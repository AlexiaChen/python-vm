#include "object/klass.hpp"
#include "object/hiInteger.hpp"
#include "object/hiString.hpp"
#include "runtime/universe.hpp"

int Klass::compare_klass(Klass* x, Klass* y) {
    if (x == y)
        return 0;

    if (x == IntegerKlass::get_instance())
        return -1;
    else if (y == IntegerKlass::get_instance())
        return 1;

    if (x->name()->less(y->name()) == (HiObject*)Universe::HiTrue)
        return -1;
    else
        return 1;
}

void Klass::print(HiObject* x) {
    printf("<object of ");
    x->klass()->name()->print();
    printf(", at %p>", x);
}

