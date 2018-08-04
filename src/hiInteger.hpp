#ifndef _HI_INTEGER_HPP
#define _HI_INTEGER_HPP

#include "hiObject.hpp"

class HiInteger : public HiObject {
private:
    int _value;

public:
    HiInteger(int x);
    int value() { return _value; }
};

#endif

