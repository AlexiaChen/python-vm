#ifndef _KLASS_HPP
#define _KLASS_HPP

#include <stdio.h>
#include <assert.h>
#include "util/arrayList.hpp"

class HiTypeObject;
class HiObject;
class HiString;
class HiDict;
class HiList;
class OopClosure;

class Klass {
private:
    HiList*       _super;
    HiList*       _mro;
    HiTypeObject* _type_object;
    HiString*     _name;
    HiDict*       _klass_dict;

    HiObject* find_and_call(HiObject* x, ObjList args, HiObject* func_name); 
public:
    Klass();

    static HiObject* create_klass(HiObject* x, HiObject* supers, HiObject* name);

    void add_super(Klass* x);
    HiTypeObject* super();
    void order_supers();

    void set_super_list(HiList* x)        { _super = x; }
    HiList* mro()                         { return _mro; }

    void set_type_object(HiTypeObject* x) { _type_object = x; }
    HiTypeObject* type_object()           { return _type_object; }

    void set_name(HiString* x)            { _name = x; }
    HiString* name()                      { assert(_name); return _name; }

    void set_klass_dict(HiDict* dict)     { _klass_dict = dict; }
    HiDict* klass_dict()                  { return _klass_dict; }

    static int compare_klass(Klass* x, Klass* y);

    virtual void print(HiObject* obj);

    virtual HiObject* greater  (HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* less     (HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* equal    (HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* not_equal(HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* ge       (HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* le       (HiObject* x, HiObject* y) { return 0; }

    virtual HiObject* add(HiObject* x, HiObject* y);
    virtual HiObject* sub(HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* mul(HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* div(HiObject* x, HiObject* y) { return 0; }
    virtual HiObject* mod(HiObject* x, HiObject* y) { return 0; }

    virtual HiObject* subscr   (HiObject* x, HiObject* y);
    virtual void store_subscr  (HiObject* x, HiObject* y, HiObject* z);
    virtual void del_subscr    (HiObject* x, HiObject* y) { return; }
    virtual HiObject* contains (HiObject* x, HiObject* y) { return 0; }

    virtual HiObject* getattr  (HiObject* x, HiObject* y);
    virtual HiObject* setattr  (HiObject* x, HiObject* y, HiObject* z);

    virtual HiObject* call(ArrayList<HiObject*>* args) { return 0; }
    virtual HiObject* allocate_instance(HiObject* type_object, ArrayList<HiObject*>* args);

    virtual HiObject* iter(HiObject* x) { return 0; }
    virtual HiObject* len(HiObject* x);
};

#endif
