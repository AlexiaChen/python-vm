#include "runtime/universe.hpp"
#include "object/hiInteger.hpp"
#include "object/hiObject.hpp"
#include "object/hiString.hpp"
#include "object/hiDict.hpp"

HiObject* Universe::HiTrue   = NULL;
HiObject* Universe::HiFalse  = NULL;

HiObject*  Universe::HiNone   = NULL;

ArrayList<Klass*>* Universe::klasses   = NULL;

void Universe::genesis() {
    HiTrue       = new HiInteger(1);
    HiFalse      = new HiInteger(0);

    HiNone       = new HiObject();

    klasses = new ArrayList<Klass*>();

    Klass* object_klass = ObjectKlass::get_instance();
    Klass* type_klass   = TypeKlass::get_instance();

    HiTypeObject* tp_obj = new HiTypeObject();
    tp_obj->set_own_klass(type_klass);
    type_klass->set_super(object_klass);

    HiTypeObject* obj_obj = new HiTypeObject();
    obj_obj->set_own_klass(object_klass);
    object_klass->set_super(NULL);

    DictKlass::get_instance()->initialize();
    StringKlass::get_instance()->initialize();

    type_klass->set_klass_dict(new HiDict());
    object_klass->set_klass_dict(new HiDict());

    type_klass->set_name(new HiString("type"));
    object_klass->set_name(new HiString("object"));
}

void Universe::destroy() {
}

