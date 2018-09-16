#ifndef _HI_STRING_HPP
#define _HI_STRING_HPP

#include "object/hiObject.hpp"

class StringKlass : public Klass {
private:
    StringKlass();
    static StringKlass* instance;

public:
    static StringKlass* get_instance();

    virtual HiObject* equal    (HiObject* x, HiObject* y);

    virtual void print(HiObject* obj);
    virtual HiObject* less   (HiObject* x, HiObject* y);
    virtual HiObject* subscr (HiObject* x, HiObject* y);
};

class HiString : public HiObject {
private:
    char* _value;
    int   _length;

public:
    HiString(const char * x);
    HiString(const char * x, const int length);

    const char* value()     { return _value; }
    int length()            { return _length; }
};

#endif
