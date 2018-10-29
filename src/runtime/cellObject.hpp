#ifndef CELL_OBJECT_HPP
#define CELL_OBJECT_HPP

#include "object/klass.hpp"
#include "object/hiObject.hpp"

class CellKlass : public Klass {
private:
    CellKlass();
    static CellKlass* _instance;

public:
    static CellKlass* get_instance();

    virtual void oops_do(OopClosure* closure, HiObject* obj);
    virtual size_t size();
};

class CellObject : public HiObject {
friend class CellKlass;

private:
    HiList* _table;
    int _index;

public:
    CellObject(HiList* l, int i);
    HiObject* value();
};

#endif
