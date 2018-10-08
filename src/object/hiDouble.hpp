#ifndef HI_DOUBLE_HPP
#define HI_DOUBLE_HPP

#include "object/hiObject.hpp"

class DoubleKlass : public Klass {
private:
    DoubleKlass();
    static DoubleKlass* instance;

public:
    static DoubleKlass* get_instance();
    void initialize();

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

    virtual HiObject* allocate_instance(HiObject* callable, 
            ArrayList<HiObject*>* args);

    virtual size_t size();
    virtual void oops_do(OopClosure* f, HiObject* obj);
};

class HiDouble : public HiObject {
private:
    double _value;

public:
    HiDouble(double x);
    double value() { return _value; }
};

#endif
