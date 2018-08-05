#ifndef _HI_OBJECT_HPP
#define _HI_OBJECT_HPP

class HiObject {
public:
    virtual void print() {}

    virtual HiObject* add(HiObject* x){}
};

#endif

