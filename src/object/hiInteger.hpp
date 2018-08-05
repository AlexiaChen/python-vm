#ifndef _HI_INTEGER_HPP
#define _HI_INTEGER_HPP

#include "object/hiObject.hpp"

class HiInteger : public HiObject {
private:
    int _value;

public:
    HiInteger(int x);
    int value() { return _value; }

    virtual void print();
    virtual HiObject* add(HiObject* x);
};

#endif

