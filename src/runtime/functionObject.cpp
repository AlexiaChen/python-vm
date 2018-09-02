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

    set_klass(FunctionKlass::get_instance());
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

