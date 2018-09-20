#ifndef _HI_INTEGER_HPP
#define _HI_INTEGER_HPP

#include "object/klass.hpp"
#include "object/hiObject.hpp"

class IntegerKlass : public Klass {
private:
    IntegerKlass();
    static IntegerKlass* instance;

public:
    static IntegerKlass* get_instance();

    virtual void print(HiObject* obj);

    virtual HiObject* greater  (HiObject* x, HiObject* y);
    virtual HiObject* less     (HiObject* x, HiObject* y);
    virtual HiObject* equal    (HiObject* x, HiObject* y);
    virtual HiObject* not_equal(HiObject* x, HiObject* y);
    virtual HiObject* ge       (HiObject* x, HiObject* y);
    virtual HiObject* le       (HiObject* x, HiObject* y);

    virtual HiObject* add(HiObject* x, HiObject* y);
    virtual HiObject* sub(HiObject* x, HiObject* y);
    virtual HiObject* mul(HiObject* x, HiObject* y);
    virtual HiObject* div(HiObject* x, HiObject* y);
    virtual HiObject* mod(HiObject* x, HiObject* y);

    virtual HiObject* allocate_instance(ArrayList<HiObject*>* args);
};

class HiInteger : public HiObject {
private:
    int _value;

public:
    HiInteger(int x);
    int value() { return _value; }
};

#endif

