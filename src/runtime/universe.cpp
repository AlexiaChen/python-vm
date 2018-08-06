#include "runtime/universe.hpp"
#include "object/hiInteger.hpp"
#include "object/hiObject.hpp"

HiInteger* Universe::HiTrue   = NULL;
HiInteger* Universe::HiFalse  = NULL;

HiObject*  Universe::HiNone   = NULL;

void Universe::genesis() {
    HiTrue       = new HiInteger(1);
    HiFalse      = new HiInteger(0);

    HiNone       = new HiObject();
}

void Universe::destroy() {
}

