#include "object/hiString.hpp"
#include "object/hiInteger.hpp"
#include "object/hiDict.hpp"
#include "runtime/universe.hpp"
#include "runtime/functionObject.hpp"
#include "memory/heap.hpp"
#include "memory/oopClosure.hpp"
#include <string.h>

StringKlass* StringKlass::instance = NULL;

StringKlass* StringKlass::get_instance() {
    if (instance == NULL)
        instance = new StringKlass();

    return instance;
}

StringKlass::StringKlass() {
}

void StringKlass::initialize() {
    (new HiTypeObject())->set_own_klass(this);

    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("upper"), new FunctionObject(string_upper));
    set_klass_dict(klass_dict);

    set_name(new HiString("str"));
    add_super(ObjectKlass::get_instance());
}

HiObject* StringKlass::equal(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiString* sx = (HiString*) x;
    HiString* sy = (HiString*) y;

    assert(sx && sx->klass() == (Klass*)this);
    assert(sy && sy->klass() == (Klass*)this);

    if (sx->length() != sy->length())
        return Universe::HiFalse;

    for (int i = 0; i < sx->length(); i++) {
        if (sx->value()[i] != sy->value()[i])
            return Universe::HiFalse;
    }

    return Universe::HiTrue;
}

void StringKlass::print(HiObject* obj) {
    HiString* str_obj = (HiString*) obj;
    assert(str_obj && str_obj->klass() == (Klass*)this);

    for (int i = 0; i < str_obj->length(); i++) {
        printf("%c", str_obj->value()[i]);
    }
}

HiObject* StringKlass::subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == (Klass*) this);
    assert(y && y->klass() == (Klass*) IntegerKlass::get_instance());

    HiString * sx = (HiString*)x;
    HiInteger* iy = (HiInteger*)y;
    
    return new HiString(&(sx->value()[iy->value()]), 1);
}

HiString::HiString(const char* x) {
    _length = strlen(x);
    _value = (char*)Universe::heap->allocate(_length);
    strcpy(_value, x);

    set_klass(StringKlass::get_instance());
}

HiString::HiString(const char * x, const int length) {
    _length = length;
    _value = (char*)Universe::heap->allocate(_length);

    // do not use strcpy here, since '\0' is allowed.
    for (int i = 0; i < length; i++) {
        _value[i] = x[i];
    }

    set_klass(StringKlass::get_instance());
}

HiObject* StringKlass::less(HiObject* x, HiObject* y) {
    HiString* sx = (HiString*) x;
    assert(sx && (sx->klass() == (Klass *)this));

    if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::HiTrue;
        else
            return Universe::HiFalse;
    }

    HiString* sy = (HiString*)y;
    assert(sy && (sy->klass() == (Klass *)this));

    int len = sx->length() < sy->length() ?
        sx->length() : sy->length();

    for (int i = 0; i < len; i++) {
        if (sx->value()[i] < sy->value()[i])
            return Universe::HiTrue;
        else if (sx->value()[i] > sy->value()[i])
            return Universe::HiFalse;
    }

    if (sx->length() < sy->length()) {
        return Universe::HiTrue;
    }

    return Universe::HiFalse;
}

HiObject* StringKlass::allocate_instance(HiObject* callable, 
        ArrayList<HiObject*>* args) {
    if (!args || args->length() == 0)
        return new HiString("");
    else
        return NULL;
}

HiObject* StringKlass::len(HiObject* x) {
    return new HiInteger(((HiString*)x)->length());
}

void StringKlass::oops_do(OopClosure* closure, HiObject* obj) {
    HiString* str_obj = (HiString*) obj;
    assert(str_obj && str_obj->klass() == (Klass*)this);

    closure->do_raw_mem(str_obj->value_address(), str_obj->length());
}

size_t StringKlass::size() {
    return sizeof(HiString);
}

