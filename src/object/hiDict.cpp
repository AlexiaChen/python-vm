#include "object/hiDict.hpp"
#include "object/hiList.hpp"
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
    klass_dict->put(new HiString("remove"),
            new FunctionObject(dict_remove));
    klass_dict->put(new HiString("keys"),
            new FunctionObject(dict_keys));
    klass_dict->put(new HiString("values"),
            new FunctionObject(dict_values));
    klass_dict->put(new HiString("items"),
            new FunctionObject(dict_items));
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
    return new DictIterator((HiDict*)x);
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

DictIterator::DictIterator(HiDict* dict) {
    _owner = dict;
    _iter_cnt = 0;
    set_klass(DictIteratorKlass::get_instance());
}

DictIteratorKlass::DictIteratorKlass() {
    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("next"), 
            new FunctionObject(dictiterator_next));
    set_klass_dict(klass_dict);
}

HiObject* dict_set_default(ObjList args) {
    HiDict* dict = (HiDict*)(args->get(0));
    HiObject* key = args->get(1);
    HiObject* value = args->get(2);

    if (!dict->has_key(key))
        dict->put(key, value);

    return Universe::HiNone;
}

HiObject* dict_remove(ObjList args) {
    HiObject* x = args->get(0);
    HiObject* y = args->get(1);

    ((HiDict*)x)->remove(y);

    return Universe::HiNone;
}

HiObject* dict_keys(ObjList args) {
    HiDict* x = (HiDict*)(args->get(0));

    HiList* keys = new HiList();

    for (int i = 0; i < x->size(); i++) {
        keys->append(x->map()->get_key(i));
    }

    return keys;
}

HiObject* dict_values(ObjList args) {
    HiDict* x = (HiDict*)(args->get(0));

    HiList* values = new HiList();

    for (int i = 0; i < x->size(); i++) {
        values->append(x->map()->get_value(i));
    }

    return values;
}

HiObject* dict_items(ObjList args) {
    HiDict* x = (HiDict*)(args->get(0));

    HiList* items = new HiList();

    for (int i = 0; i < x->size(); i++) {
        HiList* item = new HiList();
        item->append(x->map()->get_key(i));
        item->append(x->map()->get_value(i));
        items->append(item);
    }

    return items;
}

HiObject* dictiterator_next(ObjList args) {
    DictIterator* iter = (DictIterator*)(args->get(0));

    HiDict* adict = iter->owner();
    int iter_cnt = iter->iter_cnt();
    if (iter_cnt < adict->map()->size()) {
        HiObject* obj = adict->map()->get_key(iter_cnt);
        iter->inc_cnt();
        return obj;
    }
    else // TODO : we need Traceback here to mark iteration end
        return NULL;
}

