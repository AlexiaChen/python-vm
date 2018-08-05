#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "code/bytecode.hpp"
#include "code/codeObject.hpp"

class Interpreter {
private:
    ArrayList<HiObject*>* _stack;
    ArrayList<HiObject*>* _consts;
public:
    Interpreter();

    void run(CodeObject* codes);
};

#endif

