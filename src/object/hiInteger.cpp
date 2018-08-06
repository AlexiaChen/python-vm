#include "object/hiInteger.hpp"
#include "runtime/universe.hpp"

#include <stdio.h>

HiInteger::HiInteger(int x) {
    _value = x;
}

void HiInteger::print() {
    printf("%d", _value);
}

HiObject* HiInteger::add(HiObject* x) {
    return new HiInteger(_value + ((HiInteger*)x)->_value);
}

HiObject* HiInteger::greater(HiObject* x) {
    if (_value > ((HiInteger*)x)->_value)
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* HiInteger::less(HiObject* x) {
    if (_value < ((HiInteger*)x)->_value)
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* HiInteger::le(HiObject* x) {
    if (_value <= ((HiInteger*)x)->_value)
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* HiInteger::ge(HiObject* x) {
    if (_value >= ((HiInteger*)x)->_value)
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* HiInteger::equal(HiObject* x) {
    if (_value == ((HiInteger*)x)->_value)
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* HiInteger::not_equal(HiObject* x) {
    if (_value != ((HiInteger*)x)->_value)
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

