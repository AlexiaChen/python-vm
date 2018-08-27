#include "runtime/frameObject.hpp"
#include "runtime/functionObject.hpp"
#include "object/hiString.hpp"

// this constructor is used for module only.
FrameObject::FrameObject(CodeObject* codes) {
    _consts  = codes->_consts;
    _names   = codes->_names;
    
    _locals  = new Map<HiObject*, HiObject*>();
    _globals = _locals;
    _fast_locals = NULL;

    _stack   = new ArrayList<HiObject*>();
    _loop_stack  = new ArrayList<Block*>();

    _codes   = codes;
    _pc      = 0;
    _sender  = NULL;
}

FrameObject::FrameObject (FunctionObject* func, ObjList args) {
    _codes   = func->_func_code;
    _consts  = _codes->_consts;
    _names   = _codes->_names;

    _locals  = new Map<HiObject*, HiObject*>();
    _globals = func->_globals;
    _fast_locals = NULL;

    if (args) {
        _fast_locals = new ArrayList<HiObject*>();

        for (int i = 0; i < args->length(); i++) {
            _fast_locals->set(i, args->get(i));
        }
    }

    _stack   = new ArrayList<HiObject*>();
    _loop_stack  = new ArrayList<Block*>();

    _pc      = 0;
    _sender  = NULL;
}

int FrameObject::get_op_arg() {
    int byte1 = _codes->_bytecodes->value()[_pc++] & 0xff;
    int byte2 = _codes->_bytecodes->value()[_pc++] & 0xff;
    return byte2 << 8 | byte1;
}

unsigned char FrameObject::get_op_code() {
    return _codes->_bytecodes->value()[_pc++];
}

bool FrameObject::has_more_codes() {
    return _pc < _codes->_bytecodes->length();
}
