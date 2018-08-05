#ifndef _HI_OBJECT_HPP
#define _HI_OBJECT_HPP

class HiObject {
public:
    virtual void print() {}

    virtual HiObject* add(HiObject* x){}
    virtual HiObject* greater  (HiObject* x) {};
    virtual HiObject* less     (HiObject* x) {};
    virtual HiObject* equal    (HiObject* x) {};
    virtual HiObject* not_equal(HiObject* x) {};
    virtual HiObject* ge       (HiObject* x) {};
    virtual HiObject* le       (HiObject* x) {};
};

#endif

