#include "runtime/universe.hpp"
#include "object/hiInteger.hpp"
#include "object/hiObject.hpp"
#include "object/hiString.hpp"
#include "runtime/functionObject.hpp"

HiInteger* Universe::HiTrue   = NULL;
HiInteger* Universe::HiFalse  = NULL;

HiObject*  Universe::HiNone   = NULL;

void Universe::genesis() {
    HiTrue       = new HiInteger(1);
    HiFalse      = new HiInteger(0);

    HiNone       = new HiObject();

    HiDict* klass_dict = new HiDict();
    StringKlass::get_instance()->set_klass_dict(klass_dict);
    klass_dict->put(new HiString("upper"), new FunctionObject(string_upper));
}

void Universe::destroy() {
}

