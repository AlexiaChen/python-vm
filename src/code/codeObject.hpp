#ifndef CODE_OBJECT_HPP
#define CODE_OBJECT_HPP

#include "object/hiObject.hpp"

class HiString;

template <typename T>
class ArrayList;

class CodeKlass : public Klass {
private:
    CodeKlass();
    static CodeKlass* instance;

public:
    static CodeKlass* get_instance();

    virtual void oops_do(OopClosure* closure, HiObject* obj);
    virtual size_t size();
};

class CodeObject : public HiObject {
public:
    int _argcount;
    int _nlocals;
    int _stack_size;
    int _flag;

    HiString* _bytecodes;
    ArrayList<HiObject*>*  _names;
    ArrayList<HiObject*>*  _consts;
    ArrayList<HiObject*>*  _var_names;

    ArrayList<HiObject*>*  _free_vars;
    ArrayList<HiObject*>*  _cell_vars;

    HiString* _co_name;
    HiString* _file_name;

    int _lineno;
    HiString* _notable;
    CodeObject(int argcount, int nlocals, int stacksize, int flag, HiString* bytecodes,
        ArrayList<HiObject*>* consts, ArrayList<HiObject*>* names, 
        ArrayList<HiObject*>* varnames, 
        ArrayList<HiObject*>* freevars, ArrayList<HiObject*>* cellvars,
        HiString* file_name, HiString* co_name, int lineno, HiString* notable);
};

#endif

