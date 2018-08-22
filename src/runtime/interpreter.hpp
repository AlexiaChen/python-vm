#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "code/bytecode.hpp"
#include "code/codeObject.hpp"

class FrameObject;

class Interpreter {
private:
    FrameObject* _frame;

public:
    Interpreter();

    void run(CodeObject* codes);
    void build_frame(HiObject* callable);
    void leave_frame(HiObject* ret_value);
};

#endif

