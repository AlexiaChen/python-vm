#include "inc/railgun.hpp"

#include <math.h>

double get_double(ObjList args) {
    HiObject* x = args->get(0);
    double y = 0;
    if (x->klass() == IntegerKlass::get_instance()) {
        y = ((HiInteger*)x)->value();
    }
    else if (x->klass() == DoubleKlass::get_instance()) {
        y = ((HiDouble*)x)->value();
    }
    return y;
}

HiObject* math_sqrt(ObjList args) {
    double x = get_double(args);
    return new HiDouble(sqrt(x));
}

HiObject* math_sin(ObjList args) {
    double x = get_double(args);
    return new HiDouble(sin(x));
}

RGMethod math_methods[] = {
    { "sin",  math_sin,  0, "sin(x)", },
    { "sqrt", math_sqrt, 0, "square root of x", },
    { NULL, NULL, 0, NULL, },
};

#ifdef __cplusplus
extern "C" {
#endif

SO_PUBLIC RGMethod* init_libmath() {
    return math_methods;
}

#ifdef __cplusplus
}
#endif
