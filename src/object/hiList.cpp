#include "object/hiList.hpp"
#include "object/hiInteger.hpp"
#include "object/hiString.hpp"
#include "runtime/universe.hpp"
#include "runtime/functionObject.hpp"
#include <assert.h>

ListKlass* ListKlass::instance = NULL;

ListKlass* ListKlass::get_instance() {
    if (instance == NULL)
        instance = new ListKlass();

    return instance;
}

ListKlass::ListKlass() {
    HiDict * klass_dict = new HiDict();
    klass_dict->put(new HiString("append"), 
        new FunctionObject(list_append));
    klass_dict->put(new HiString("pop"), 
        new FunctionObject(list_pop));
    klass_dict->put(new HiString("remove"), 
        new FunctionObject(list_remove));
    klass_dict->put(new HiString("reverse"), 
        new FunctionObject(list_reverse));
    klass_dict->put(new HiString("sort"), 
        new FunctionObject(list_sort));
    set_klass_dict(klass_dict);

    set_name(new HiString("list"));
}

void ListKlass::print(HiObject* x) {
    HiList * lx = (HiList*)x;
    assert(lx && lx->klass() == (Klass*) this);

    printf("[");

    int size = lx->_inner_list->size();
    if (size >= 1)
        lx->_inner_list->get(0)->print();

    for (int i = 1; i < size; i++) {
        printf(", ");
        lx->_inner_list->get(i)->print();
    }
    printf("]");
}

HiObject* ListKlass::subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == (Klass*) this);
    assert(y && y->klass() == (Klass*) IntegerKlass::get_instance());

    HiList * lx = (HiList*)x;
    HiInteger* iy = (HiInteger*)y;
    
    return lx->inner_list()->get(iy->value());
}

void ListKlass::store_subscr(HiObject* x, HiObject* y, HiObject* z) {
    assert(x && x->klass() == (Klass*) this);
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiList * lx = (HiList*)x;
    HiInteger* iy = (HiInteger*)y;
    
    lx->inner_list()->set(iy->value(), z);
}

void ListKlass::del_subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == (Klass*) this);
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiList * lx = (HiList*)x;
    HiInteger* iy = (HiInteger*)y;
    
    lx->inner_list()->delete_index(iy->value());
}

HiObject* ListKlass::contains(HiObject* x, HiObject* y) {
    HiList * lx = (HiList*)x;
    assert(lx && lx->klass() == (Klass*) this);

    int size = lx->_inner_list->size();
    for (int i = 1; i < size; i++) {
        if (lx->_inner_list->get(i)->equal(y))
            return Universe::HiTrue;
    }

    return Universe::HiFalse;
}

HiObject* ListKlass::iter(HiObject* x) {
    return Universe::HiNone;
}

HiObject* ListKlass::less(HiObject* x, HiObject* y) {
    HiList * lx = (HiList*)x;
    assert(lx && lx->klass() == (Klass*) this);

    if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::HiTrue;
        else
            return Universe::HiFalse;
    }

    HiList * ly = (HiList*)y;
    assert(ly && ly->klass() == (Klass*) this);

    int len = lx->size() < ly->size() ?
        lx->size() : ly->size();

    for (int i = 0; i < len; i++) {
        if (lx->get(i)->less(ly->get(i)) == Universe::HiTrue) {
            return Universe::HiTrue;
        }
        else if (lx->get(i)->equal(ly->get(i)) != Universe::HiTrue) {
            return Universe::HiFalse;
        }
    }

    if (lx->size() < ly->size())
        return Universe::HiTrue;

    return Universe::HiFalse;
}

HiList::HiList() {
    set_klass(ListKlass::get_instance());
    _inner_list = new ArrayList<HiObject*>();
}

HiList::HiList(ObjList ol) {
    set_klass(ListKlass::get_instance());
    _inner_list = ol;
}

HiObject* list_append(ObjList args) {
    ((HiList*)(args->get(0)))->append(args->get(1));
    return Universe::HiNone;
}

HiObject* list_sort(ObjList args) {
    HiList* list = (HiList*)(args->get(0));
    assert(list && list->klass() == ListKlass::get_instance());

    // bubble sort
    for (int i = 0; i < list->size(); i++) {
        for (int j = list->size() - 1; j > i; j--) {
            if (list->get(j)->less(list->get(j-1)) == Universe::HiTrue) {
                HiObject* t = list->get(j);
                list->set(j, list->get(j-1));
                list->set(j-1, t);
            }
        }
    }

    return Universe::HiNone;
}

HiObject* list_pop(ObjList args) {
    HiList* list = (HiList*)(args->get(0));
    assert(list && list->klass() == ListKlass::get_instance());
    return list->pop();
}

HiObject* list_remove(ObjList args) {
    HiList* list = (HiList*)(args->get(0));
    HiObject* target = (HiObject*)(args->get(1));

    assert(list && list->klass() == ListKlass::get_instance());

    for (int i = 0; i < list->inner_list()->size(); i++) {
        if (list->get(i)->equal(target) == (HiObject*)Universe::HiTrue) {
            list->inner_list()->delete_index(i);
        }
    }

    return Universe::HiNone;
}

HiObject* list_reverse(ObjList args) {
    HiList* list = (HiList*)(args->get(0));

    int i = 0;
    int j = list->size() - 1;
    while (i < j) {
        HiObject* t = list->get(i);
        list->set(i, list->get(j));
        list->set(j, t);

        i++;
        j--;
    }

    return Universe::HiNone;
}

/*
 * List Iterators
 */
ListIteratorKlass* ListIteratorKlass::instance = NULL;

ListIteratorKlass* ListIteratorKlass::get_instance() {
    if (instance == NULL)
        instance = new ListIteratorKlass();

    return instance;
}

HiObject* ListIteratorKlass::next(HiObject* x) {
    return NULL;
}


