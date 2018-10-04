#include "runtime/frameObject.hpp"
#include "runtime/functionObject.hpp"
#include "object/hiString.hpp"
#include "object/hiList.hpp"
#include "object/hiDict.hpp"
#include "memory/oopClosure.hpp"

// this constructor is used for module only.
FrameObject::FrameObject(CodeObject* codes) {
    _consts  = codes->_consts;
    _names   = codes->_names;
    
    _locals  = new HiDict();
    _globals = _locals;
    _fast_locals = NULL;

    _stack   = new HiList();
    _loop_stack  = new ArrayList<Block*>();

    _codes   = codes;
    _pc      = 0;
    _sender  = NULL;
    _entry_frame = false;
}

FrameObject::FrameObject (FunctionObject* func, ObjList args) {
    _codes   = func->_func_code;
    _consts  = _codes->_consts;
    _names   = _codes->_names;

    _locals  = new HiDict();
    _globals = func->_globals;
    _fast_locals = new HiList();

    if (func->_defaults) {
        int dft_cnt = func->_defaults->length();
        int argcnt  = _codes->_argcount;

        while (dft_cnt--) {
            _fast_locals->set(--argcnt, func->_defaults->get(dft_cnt));
        }
    }

    if (args) {
        for (int i = 0; i < args->length(); i++) {
            _fast_locals->set(i, args->get(i));
        }
    }

    _stack   = new HiList();
    _loop_stack  = new ArrayList<Block*>();

    _pc      = 0;
    _sender  = NULL;
    _entry_frame = false;
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

void FrameObject::oops_do(OopClosure* f) {
    f->do_array_list(&_consts);
    f->do_array_list(&_names);

    f->do_oop((HiObject**)&_globals);
    f->do_oop((HiObject**)&_locals);

    f->do_oop((HiObject**)&_fast_locals);
    f->do_oop((HiObject**)&_stack);

    f->do_oop((HiObject**)&_codes);

    if (_sender)
        _sender->oops_do(f);
}

