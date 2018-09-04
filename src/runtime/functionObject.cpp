#include "object/hiInteger.hpp"
#include "object/hiString.hpp"
#include "runtime/universe.hpp"
#include "runtime/functionObject.hpp"

FunctionKlass* FunctionKlass::instance = NULL;

FunctionKlass* FunctionKlass::get_instance() {
    if (instance == NULL)
        instance = new FunctionKlass();

    return instance;
}

FunctionKlass::FunctionKlass() {
}

void FunctionKlass::print(HiObject* obj) {
    printf("<function : ");
    FunctionObject* fo = static_cast<FunctionObject*>(obj);

    assert(fo && fo->klass() == (Klass*) this);
    fo->func_name()->print();
    printf(">");
}

FunctionObject::FunctionObject(HiObject* code_object) {
    CodeObject* co = (CodeObject*) code_object;

    _func_code = co;
    _func_name = co->_co_name;
    _flags     = co->_flag;
    _globals   = NULL;

    set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(NativeFuncPointer nfp) {
    _func_code = NULL;
    _func_name = NULL;
    _flags     = 0;
    _globals   = NULL;
    _native_func = nfp;

    set_klass(NativeFunctionKlass::get_instance());
}

void FunctionObject::set_default(ArrayList<HiObject*>* defaults) {
    if (defaults == NULL) {
        _defaults = NULL;
        return;
    }

    _defaults = new ArrayList<HiObject*>(defaults->length());

    for (int i = 0; i < defaults->length(); i++) {
        _defaults->set(i, defaults->get(i));
    }
}

/*
 * Operations for native calls.
 */

NativeFunctionKlass* NativeFunctionKlass::instance = NULL;

NativeFunctionKlass* NativeFunctionKlass::get_instance() {
    if (instance == NULL)
        instance = new NativeFunctionKlass();

    return instance;
}

NativeFunctionKlass::NativeFunctionKlass() {
    set_super(FunctionKlass::get_instance());
}

HiObject* FunctionObject::call(ObjList args) {
    return (*_native_func)(args);
}

/*
 *  Operations for methods
 *  Method is a wrapper for function.
 */
MethodKlass* MethodKlass::instance = NULL;

MethodKlass* MethodKlass::get_instance() {
    if (instance == NULL)
        instance = new MethodKlass();

    return instance;
}

MethodKlass::MethodKlass() {
    set_klass_dict(new HiDict());
    set_super(FunctionKlass::get_instance());
}

/*
 * To check the type of a callable object.
 */
bool MethodObject::is_native(HiObject *x) {
    Klass* k = x->klass();
    if (k == (Klass*) NativeFunctionKlass::get_instance())
        return true;

    while (k->super() != NULL) {
        k = k->super();
        if (k == (Klass*) NativeFunctionKlass::get_instance())
            return true;
    }
    return false;
}

bool MethodObject::is_method(HiObject *x) {
    if (x->klass() == (Klass*) MethodKlass::get_instance())
        return true;

    return false;
}

bool MethodObject::is_function(HiObject *x) {
    Klass* k = x->klass();
    if (k == (Klass*) FunctionKlass::get_instance())
        return true;

    while (k->super() != NULL) {
        k = k->super();
        if (k == (Klass*) FunctionKlass::get_instance())
            return true;
    }

    return false;
}

HiObject* len(ObjList args) {
    HiObject* arg0 = args->get(0);
    assert(arg0->klass() == StringKlass::get_instance());

    return new HiInteger(((HiString*)arg0)->length());
}

HiObject* string_upper(ObjList args) {
    HiObject* arg0 = args->get(0);
    assert(arg0->klass() == StringKlass::get_instance());

    HiString* str_obj = (HiString*)arg0;

    int length = str_obj->length();
    if (length <= 0)
        return Universe::HiNone;

    char* v = new char[length];
    char c;
    for (int i = 0; i < length; i++) {
        c = str_obj->value()[i];
        if (c >= 'a' && c <= 'z')
            v[i] = c - 0x20;
        else
            v[i] = c;
    }

    return new HiString(v, length);
}
