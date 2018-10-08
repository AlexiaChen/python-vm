#ifndef _UNIVERSE_HPP
#define _UNIVERSE_HPP

#include <stdio.h>

class Klass;
class Heap;
class HiInteger;
class HiObject;
class OopClosure;
class CodeObject;

template <typename T>
class ArrayList;

class Universe {
public:
    static HiObject* HiTrue;
    static HiObject* HiFalse;

    static HiObject* HiNone;
    static ArrayList<Klass*>* klasses;

    static CodeObject* main_code;
    static Heap* heap;

    static HiObject* stop_iteration;
public:
    static void genesis();
    static void destroy();
    static void oops_do(OopClosure* closure);
};

#endif

