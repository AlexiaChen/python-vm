#include "object/hiDict.hpp"
#include "runtime/module.hpp"
#include "util/bufferedInputStream.hpp"
#include "code/binaryFileParser.hpp"
#include "runtime/interpreter.hpp"

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
    HiString* file_name = (HiString*)(mod_name->add(new HiString(".pyc")));
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

