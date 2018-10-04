#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "code/bytecode.hpp"
#include "code/codeObject.hpp"

class FrameObject;
class HiDict;
class OopClosure;
class ModuleObject;

class Interpreter {
private:
    ModuleObject*         _builtins;
    HiDict*               _modules;
    FrameObject*          _frame;
    HiObject*             _ret_value;

    static Interpreter*   _instance;
    Interpreter();

    void      destroy_frame   ();

public:
    static Interpreter* get_instance();
    void      initialize();

    void      run             (CodeObject* codes);
    HiDict*   run_mod         (CodeObject* codes, HiString* mod_name);
    void      build_frame     (HiObject* callable, ObjList args);
    void      enter_frame     (FrameObject* frame);
    void      eval_frame      ();
    void      leave_frame     ();
    HiObject* call_virtual    (HiObject* func, ObjList args);

    void      oops_do         (OopClosure* f);
};

#endif

