#include "object/hiDict.hpp"
#include "object/hiInteger.hpp"
#include "object/hiString.hpp"
#include "runtime/functionObject.hpp"
#include "runtime/universe.hpp"
#include <assert.h>

DictKlass* DictKlass::instance = NULL;

DictKlass* DictKlass::get_instance() {
    if (instance == NULL) {
        instance = new DictKlass();
    }

    return instance;
}

DictKlass::DictKlass() {
}

void DictKlass::initialize() {
    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("setdefault"),
            new FunctionObject(dict_set_default));
    set_klass_dict(klass_dict);
}

void DictKlass::print(HiObject* obj) {
    HiDict* dict_obj = (HiDict*) obj;
    assert(dict_obj && dict_obj->klass() == (Klass*) this);

    printf("{");   
    int size = dict_obj->_map->size();
    if (size >= 1) {
        dict_obj->_map->entries()[0]._k->print();
        printf(":");   
        dict_obj->_map->entries()[0]._v->print();
    }

    for (int i = 1; i < size; i++) {
        printf(", ");   
        dict_obj->_map->entries()[i]._k->print();
        printf(":");   
        dict_obj->_map->entries()[i]._v->print();
    }

    printf("}");
}

size_t DictKlass::size() {
    return sizeof(HiDict);
}

HiObject* DictKlass::getattr(HiObject* obj, HiString* name) {
    assert(obj->klass() == (Klass*) this);
    return klass_dict()->get((HiObject*)name);
}

HiObject* DictKlass::subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == (Klass*) this);
    return ((HiDict*)x)->map()->get(y);
}

void DictKlass::store_subscr(HiObject* x, HiObject*y, HiObject* z) {
    assert(x && x->klass() == (Klass*) this);
    ((HiDict*)x)->put(y, z);
}

HiObject* DictKlass::iter(HiObject* x) {
    HiObject* obj = new HiObject();
    return obj;
}

void DictKlass::del_subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == (Klass*) this);
    ((HiDict*)x)->remove(y);
}

HiDict::HiDict() {
    _map = new Map<HiObject*, HiObject*>();
    set_klass(DictKlass::get_instance());
}

HiDict::HiDict(Map<HiObject*, HiObject*>* x) {
    _map = x;
    set_klass(DictKlass::get_instance());
}

/*
 * Iterations for dict object
 */
DictIteratorKlass* DictIteratorKlass::instance = NULL;

DictIteratorKlass* DictIteratorKlass::get_instance() {
    if (instance == NULL) {
        instance = new DictIteratorKlass();
    }

    return instance;
}

DictIteratorKlass::DictIteratorKlass() {
}

HiObject* DictIteratorKlass::next(HiObject* x) {
    HiString* attr_name = new HiString("iter_cnt");
    HiInteger* iter_cnt = (HiInteger*)(x->getattr(attr_name));

    HiDict* adict = (HiDict*)(x->getattr(new HiString("dobj")));
    if (iter_cnt->value() < adict->map()->size()) {
        HiObject* obj = adict->map()->get_key(iter_cnt->value());
        return obj;
    }
    else // TODO : we need Traceback here to mark iteration end
        return NULL;
}

HiObject* dict_set_default(ObjList args) {
    HiDict* dict = (HiDict*)(args->get(0));
    HiObject* key = args->get(1);
    HiObject* value = args->get(2);

    if (!dict->has_key(key))
        dict->put(key, value);

    return Universe::HiNone;
}

