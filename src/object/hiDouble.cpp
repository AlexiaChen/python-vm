#include "object/klass.hpp"
#include "object/hiDict.hpp"
#include "object/hiString.hpp"
#include "object/hiInteger.hpp"
#include "object/hiDouble.hpp"
#include "runtime/universe.hpp"

#include <stdio.h>

DoubleKlass* DoubleKlass::instance = NULL;

DoubleKlass::DoubleKlass() {
}

void DoubleKlass::initialize() {
    set_klass_dict(new HiDict());
    set_name(new HiString("int"));
    (new HiTypeObject())->set_own_klass(this);
    add_super(ObjectKlass::get_instance());
}

HiDouble::HiDouble(double x) {
    _value = x;
    set_klass(DoubleKlass::get_instance());
}

DoubleKlass* DoubleKlass::get_instance() {
    if (instance == NULL)
        instance = new DoubleKlass();

    return instance;
}

void DoubleKlass::print(HiObject* obj) {
    HiDouble* dbl_obj = (HiDouble*) obj;
    assert(dbl_obj && ((char *)dbl_obj->klass()) == ((char *)this));
    printf("%.12g", dbl_obj->value());
}

HiObject* DoubleKlass::allocate_instance(HiObject* callable, 
        ArrayList<HiObject*>* args) {
    if (!args || args->length() == 0)
        return new HiDouble(0);
    else
        return NULL;
}

size_t DoubleKlass::size() {
    return sizeof(HiDouble);
}

void DoubleKlass::oops_do(OopClosure* f, HiObject* obj) {
    // do nothing
    // only overwrite warning message in Klass
}

HiObject* DoubleKlass::greater(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    if (ix->value() > iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* DoubleKlass::less(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    assert(ix && (ix->klass() == (Klass *)this));

    if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::HiTrue;
        else
            return Universe::HiFalse;
    }

    HiDouble* iy = (HiDouble*)y;
    assert(iy && (iy->klass() == (Klass *)this));

    if (ix->value() < iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* DoubleKlass::equal(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    if (ix->value() == iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* DoubleKlass::not_equal(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    if (ix->value() != iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* DoubleKlass::ge(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    if (ix->value() >= iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* DoubleKlass::le(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    if (ix->value() <= iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* DoubleKlass::add(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    return new HiDouble(ix->value() + iy->value());
}

HiObject* DoubleKlass::sub(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    return new HiDouble(ix->value() - iy->value());
}

HiObject* DoubleKlass::mul(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    HiDouble* iy = (HiDouble*) y;

    assert(ix && (ix->klass() == (Klass *)this));
    assert(iy && (iy->klass() == (Klass *)this));

    return new HiDouble(ix->value() * iy->value());
}

HiObject* DoubleKlass::div(HiObject* x, HiObject* y) {
    HiDouble* ix = (HiDouble*) x;
    assert(ix && (ix->klass() == (Klass *)this));

    if (y->klass() == (Klass*)this) {
        return new HiDouble(ix->value() / 
                ((HiDouble*)y)->value());
    }
    else if (y->klass() == IntegerKlass::get_instance()) {
        return new HiDouble(ix->value() / 
                ((HiInteger*)y)->value());
    }
    else {
        //Error
    }

    return NULL;
}

HiObject* DoubleKlass::mod(HiObject* x, HiObject* y) {
    return new HiDouble(0.0);
}

