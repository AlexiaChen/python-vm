#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "code/bytecode.hpp"
#include "code/codeObject.hpp"

class FrameObject;
class HiDict;

class Interpreter {
private:
    HiDict*               _builtins;
    FrameObject*          _frame;

    static Interpreter*   _instance;
    Interpreter();

public:
    static Interpreter* get_instance();

    void run(CodeObject* codes);
    void build_frame(HiObject* callable, ObjList args);
    void leave_frame(HiObject* ret_value);
    HiObject* call_virtual    (HiObject* func, ObjList args);
};

#endif

