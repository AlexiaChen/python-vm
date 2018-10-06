#include "object/hiObject.hpp"
#include "object/hiDict.hpp"
#include "object/hiString.hpp"
#include "runtime/universe.hpp"
#include "runtime/stringTable.hpp"
#include "runtime/functionObject.hpp"
#include "memory/heap.hpp"
#include "memory/oopClosure.hpp"

ObjectKlass* ObjectKlass::instance = NULL;

ObjectKlass::ObjectKlass() {
}

ObjectKlass* ObjectKlass::get_instance() {
    if (instance == NULL)
        instance = new ObjectKlass();

    return instance;
}

void HiObject::print() {
    klass()->print(this);
}

HiObject::HiObject() {
    _mark_word = 0;
    _obj_dict = NULL;
}

HiObject* HiObject::greater(HiObject * rhs) {
    return klass()->greater(this, rhs);
}

HiObject* HiObject::add(HiObject * rhs) {
    return klass()->add(this, rhs);
}

HiObject* HiObject::sub(HiObject * rhs) {
    return klass()->sub(this, rhs);
}

HiObject* HiObject::mul(HiObject * rhs) {
    return klass()->mul(this, rhs);
}

HiObject* HiObject::div(HiObject * rhs) {
    return klass()->div(this, rhs);
}

HiObject* HiObject::mod(HiObject * rhs) {
    return klass()->mod(this, rhs);
}

HiObject* HiObject::less(HiObject * rhs) {
    return klass()->less(this, rhs);
}

HiObject* HiObject::equal(HiObject * rhs) {
    return klass()->equal(this, rhs);
}

HiObject* HiObject::not_equal(HiObject * rhs) {
    return klass()->not_equal(this, rhs);
}

HiObject* HiObject::ge(HiObject * rhs) {
    return klass()->ge(this, rhs);
}

HiObject* HiObject::le(HiObject * rhs) {
    return klass()->le(this, rhs);
}

HiObject* HiObject::getattr(HiObject* x) {
    return klass()->getattr(this, x);
}

HiObject* HiObject::get_klass_attr(HiObject* x) {
    return klass()->get_klass_attr(this, x);
}

HiObject* HiObject::setattr(HiObject* x, HiObject* y) {
    return klass()->setattr(this, x, y);
    if (klass() == TypeKlass::get_instance()) {
    }
}

HiObject* HiObject::subscr(HiObject* x) {
    return klass()->subscr(this, x);
}

void HiObject::store_subscr(HiObject* x, HiObject* y) {
    klass()->store_subscr(this, x, y);
}

void HiObject::del_subscr(HiObject* x) {
    klass()->del_subscr(this, x);
}

HiObject* HiObject::contains(HiObject* x) {
    return klass()->contains(this, x);
}

HiObject* HiObject::iter() {
    return klass()->iter(this);
}

HiObject* HiObject::next() {
    return klass()->next(this);
}

HiObject* HiObject::len() {
    return klass()->len(this);
}

/*
 * TypeObject is a special object
 */
TypeKlass* TypeKlass::instance = NULL;

TypeKlass* TypeKlass::get_instance() {
    if (instance == NULL)
        instance = new TypeKlass();

    return instance;
}

void TypeKlass::print(HiObject* obj) {
    assert(obj->klass() == (Klass*) this);
    printf("<type ");
    Klass* own_klass = ((HiTypeObject*)obj)->own_klass();

    HiDict* attr_dict = own_klass->klass_dict();
    if (attr_dict) {
        HiObject* mod = attr_dict->get((HiObject*)
                StringTable::get_instance()->mod_str);
        if (mod != Universe::HiNone) {
            mod->print();
            printf(".");
        }
    }

    own_klass->name()->print();
    printf(">");
}

HiObject* TypeKlass::setattr(HiObject* x, HiObject* y, HiObject* z) {
    HiTypeObject* type_obj = (HiTypeObject*)x;
    type_obj->own_klass()->klass_dict()->put(y, z);
    return Universe::HiNone;
}

size_t TypeKlass::size() {
    return sizeof(HiTypeObject);
}

void TypeKlass::oops_do(OopClosure* f, HiObject* obj) {
    // do nothing since HiTypeObject refers no oop.
}

HiTypeObject::HiTypeObject() {
    set_klass(TypeKlass::get_instance());
}

void HiTypeObject::set_own_klass(Klass* k) {
    _own_klass = k; 
    k->set_type_object(this);
}

void HiObject::init_dict() {
    _obj_dict = new HiDict();
}

/*
 * Interfaces for GC.
 */
void HiObject::oops_do(OopClosure* closure) {
    // object does not know who to visit, klass knows
    closure->do_oop((HiObject**)&_obj_dict);
    klass()->oops_do(closure, this);
}

char* HiObject::new_address() {
    if ((_mark_word & 0x1) == 0x1)
        return (char*)(_mark_word & ((long)-8));

    return NULL;
}

void HiObject::set_new_address(char* addr) {
    if (!addr)
        return;

    _mark_word = ((long)addr) | 0x1;
}

void* HiObject::operator new(size_t size) {
    return Universe::heap->allocate(size);
}

size_t HiObject::size() {
    return klass()->size();
}

