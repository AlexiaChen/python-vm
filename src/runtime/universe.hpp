#ifndef _UNIVERSE_HPP
#define _UNIVERSE_HPP

#include <stdio.h>

class HiInteger;
class HiObject;

class Universe {
public:
    static HiObject* HiTrue;
    static HiObject* HiFalse;

    static HiObject* HiNone;

public:
    static void genesis();
    static void destroy();
};

#endif

