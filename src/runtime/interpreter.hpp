#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "code/bytecode.hpp"
#include "code/codeObject.hpp"

class Block {
public:
    unsigned char _type;
    unsigned int  _target;
    int  _level;

    Block() {
        _type = 0;
        _target = 0;
        _level = 0;
    }

    Block(unsigned char b_type,
            unsigned int b_target,
            int b_level):
        _type(b_type),
        _target(b_target),
        _level(b_level) {
        }

    Block(const Block& b) {
        _type = b._type;
        _target = b._target;
        _level  = b._level;
    }
};

class Interpreter {
private:
    ArrayList<HiObject*>* _stack;
    ArrayList<HiObject*>* _consts;

    ArrayList<Block*>*    _loop_stack;

public:
    Interpreter();

    void run(CodeObject* codes);
};

#endif

