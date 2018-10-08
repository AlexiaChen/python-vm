#ifndef RAILGUN_HPP
#define RAILGUN_HPP

#include "runtime/functionObject.hpp"
#include "object/hiInteger.hpp"
#include "object/hiDouble.hpp"

#define SO_PUBLIC __attribute__((visibility("default")))

struct RGMethod {
    const char* meth_name;
    NativeFuncPointer meth;
    int meth_info;
    const char* meth_doc;
};

typedef RGMethod* (*INIT_FUNC)();

#endif
