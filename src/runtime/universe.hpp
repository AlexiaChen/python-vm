#ifndef _UNIVERSE_HPP
#define _UNIVERSE_HPP

#include <stdio.h>

class Klass;
class HiInteger;
class HiObject;

template <typename T>
class ArrayList;

class Universe {
public:
    static HiObject* HiTrue;
    static HiObject* HiFalse;

    static HiObject* HiNone;
    static ArrayList<Klass*>* klasses;

public:
    static void genesis();
    static void destroy();
};

#endif

