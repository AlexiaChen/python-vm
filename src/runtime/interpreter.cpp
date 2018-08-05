#include "runtime/interpreter.hpp"
#include "util/arrayList.hpp"
#include "object/hiString.hpp"
#include "object/hiInteger.hpp"

#include <string.h>

Interpreter::Interpreter() {
}

void Interpreter::run(CodeObject* codes) {
    int pc = 0;
    int code_length = codes->_bytecodes->length();

    _stack  = new ArrayList<HiObject*>(codes->_stack_size);
    _consts = codes->_consts;

    while (pc < code_length) {
        unsigned char op_code = codes->_bytecodes->value()[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

        int op_arg = -1;
        if (has_argument) {
            int byte1 = (codes->_bytecodes->value()[pc++] & 0xFF);
            op_arg = ((codes->_bytecodes->value()[pc++] & 0xFF) << 8) | byte1;
        }

        HiInteger* lhs, * rhs;
        HiObject* v, * w, * u, * attr;

        switch (op_code) {
            case ByteCode::LOAD_CONST:
                _stack->add(_consts->get(op_arg));
                break;

            case ByteCode::PRINT_ITEM:
                v = _stack->pop();
                v->print();
                break;

            case ByteCode::PRINT_NEWLINE:
                printf("\n");
                break;

            case ByteCode::BINARY_ADD:
                v = _stack->pop();
                w = _stack->pop();
                _stack->add(w->add(v));
                break;

            case ByteCode::RETURN_VALUE:
                _stack->pop(); 
                break;

            default:
                printf("Error: Unrecognized byte code %d\n", op_code);
        }
    }
}

