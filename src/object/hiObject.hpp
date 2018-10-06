#ifndef _HI_OBJECT_HPP
#define _HI_OBJECT_HPP

#include "object/klass.hpp"
#include <assert.h>

class HiString;

class ObjectKlass : public Klass {
private:
    ObjectKlass();
    static ObjectKlass* instance;

public:
    static ObjectKlass* get_instance();
};

class HiObject {
private:
    long    _mark_word;
    Klass*  _klass;
    HiDict* _obj_dict;

public:
    HiObject();
    Klass* klass()             { assert(_klass != NULL); return _klass; }
    void set_klass(Klass* x)   { _klass = x; }

    void print();

    HiObject* add(HiObject* x);
    HiObject* sub(HiObject* x);
    HiObject* mul(HiObject* x);
    HiObject* div(HiObject* x);
    HiObject* mod(HiObject* x);

    HiObject* greater  (HiObject* x);
    HiObject* less     (HiObject* x);
    HiObject* equal    (HiObject* x);
    HiObject* not_equal(HiObject* x);
    HiObject* ge       (HiObject* x);
    HiObject* le       (HiObject* x);

    HiObject* getattr  (HiObject* x);
    HiObject* setattr  (HiObject* x, HiObject* y);

    HiObject* contains (HiObject* x);
    HiObject* subscr   (HiObject* x);
    HiObject* get_klass_attr(HiObject* y);
    void      store_subscr  (HiObject* x, HiObject* y); 
    void      del_subscr    (HiObject* x); 

    HiObject* iter();
    HiObject* next();
    HiObject* len();

    HiDict* obj_dict()   { return _obj_dict; }
    void set_obj_dict(HiDict* x) { _obj_dict = x; }
    void init_dict();

    void* operator new(size_t size);

    // interfaces for GC.
    void oops_do(OopClosure* closure);
    size_t size();
    char* new_address();
    void set_new_address(char* addr);
};

/*
 * meta-klass for the object system.
 */
class TypeKlass : public Klass {
private:
    TypeKlass() {}
    static TypeKlass* instance;

public:
    static TypeKlass* get_instance();

    virtual void print(HiObject* obj);
    virtual HiObject* setattr(HiObject* x, HiObject* y, HiObject* z);

    virtual size_t size();
    virtual void oops_do(OopClosure* f, HiObject* obj);
};

class HiTypeObject : public HiObject {
private:
    Klass*  _own_klass;

public:
    HiTypeObject();

    void    set_own_klass(Klass* k);
    Klass*  own_klass()             { return _own_klass; }
};

#endif

