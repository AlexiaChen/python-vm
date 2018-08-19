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
};

#endif

