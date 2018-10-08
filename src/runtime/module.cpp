#include "object/hiDict.hpp"
#include "object/hiList.hpp"
#include "runtime/module.hpp"
#include "runtime/universe.hpp"
#include "runtime/interpreter.hpp"
#include "runtime/stringTable.hpp"
#include "util/bufferedInputStream.hpp"
#include "code/binaryFileParser.hpp"
#include "memory/oopClosure.hpp"
#include "inc/railgun.hpp"

#include <dlfcn.h>
#include <unistd.h>

#define ST(x) StringTable::get_instance()->STR(x)
#define STR(x) x##_str

ModuleKlass* ModuleKlass::_instance = NULL;

ModuleKlass* ModuleKlass::get_instance() {
    if (_instance == NULL)
        _instance = new ModuleKlass();

    return _instance;
}

ModuleKlass::ModuleKlass() {
}

void ModuleKlass::initialize() {
    HiDict* dict = new HiDict();
    set_klass_dict(dict);
    set_name(new HiString("module"));
    (new HiTypeObject())->set_own_klass(this);
    add_super(ObjectKlass::get_instance());
}

ModuleObject::ModuleObject(HiDict* dict) {
    set_obj_dict(dict);
    set_klass(ModuleKlass::get_instance());
}

ModuleObject* ModuleObject::import_module(HiObject* x) {
    HiString* mod_name = (HiString*)x;

    HiList* so_list = new HiList();
    so_list->append(ST(libdir_pre));
    so_list->append(mod_name);
    so_list->append(ST(so_suf));
    HiString* file_name = ST(empty)->join(so_list);
     
    if (access(file_name->value(), R_OK) == 0) {
        return import_so(mod_name);
    }

    file_name = (HiString*)(mod_name->add(ST(pyc_suf)));
    if (access(file_name->value(), R_OK) == -1) {
        HiList* pyc_list = new HiList();
        pyc_list->append(ST(libdir_pre));
        pyc_list->append(mod_name);
        pyc_list->append(ST(pyc_suf));
        file_name = ST(empty)->join(pyc_list);
    }

    assert(access(file_name->value(), R_OK) == 0);

    BufferedInputStream stream(file_name->value());
    BinaryFileParser parser(&stream);
    CodeObject* mod_code = parser.parse();
    HiDict* mod_dict = Interpreter::get_instance()->run_mod(mod_code, mod_name);
    return new ModuleObject(mod_dict);
}

void ModuleObject::put(HiObject* x, HiObject* y) {
    obj_dict()->put(x, y);
}

HiObject* ModuleObject::get(HiObject* x) {
    return obj_dict()->get(x);
}

void ModuleObject::extend(ModuleObject* mo) {
    obj_dict()->update(mo->obj_dict());
}

size_t ModuleKlass::size() {
    return sizeof(ModuleObject);
}

void ModuleKlass::oops_do(OopClosure* f, HiObject* obj) {
    void* temp = &(((ModuleObject*)obj)->_mod_name);
    f->do_oop((HiObject**)temp);
}

ModuleObject* ModuleObject::import_so(HiString* mod_name) {
    char* error_msg = NULL;

    HiString* prefix = new HiString("./lib/");
    HiString* so_suffix = new HiString(".so");

    HiString* file_name = (HiString*)(prefix->add(mod_name)->add(so_suffix));
    void* handle = dlopen(file_name->value(), RTLD_NOW);
    if (handle == NULL) {
        printf("error to open file: %s\n", dlerror());
        return NULL;
    }

    HiString* method_prefix = new HiString("init_");
    HiString* init_meth = (HiString*)(method_prefix->add(mod_name));
    INIT_FUNC init_func = (INIT_FUNC)dlsym(handle, init_meth->value());
    if ((error_msg = dlerror()) != NULL) {
        printf("Symbol init_methods not found: %s\n", error_msg);
        dlclose(handle);
        return NULL;
    }

    RGMethod* ml = init_func();
    ModuleObject* mod = new ModuleObject(new HiDict());
    for (; ml->meth_name != NULL; ml++) {
        mod->put(new HiString(ml->meth_name), 
                new FunctionObject(ml->meth));
    }

    return mod;
}

