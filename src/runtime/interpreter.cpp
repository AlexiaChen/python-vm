#include "runtime/interpreter.hpp"
#include "runtime/universe.hpp"
#include "util/arrayList.hpp"
#include "util/map.hpp"
#include "object/hiString.hpp"
#include "object/hiInteger.hpp"

#include <string.h>

#define PUSH(x)       _stack->add((x))
#define POP()         _stack->pop()
#define STACK_LEVEL() _stack->size()

Interpreter::Interpreter() {
}

void Interpreter::run(CodeObject* codes) {
    int pc = 0;
    int code_length = codes->_bytecodes->length();

    _stack  = new ArrayList<HiObject*>(codes->_stack_size);
    _consts = codes->_consts;
    _loop_stack = new ArrayList<Block*>();
    ArrayList<HiObject*>* names  = codes->_names;
    Map<HiObject*, HiObject*>* locals  = new Map<HiObject*, HiObject*>();

    Block* b;

    while (pc < code_length) {
        unsigned char op_code = codes->_bytecodes->value()[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT;

        int op_arg = -1;
        if (has_argument) {
            int byte1 = (codes->_bytecodes->value()[pc++] & 0xFF);
            op_arg = ((codes->_bytecodes->value()[pc++] & 0xFF) << 8) | byte1;
        }

        HiObject* v, * w, * u, * attr;

        switch (op_code) {
            case ByteCode::LOAD_CONST:
                PUSH(_consts->get(op_arg));
                break;

            case ByteCode::LOAD_NAME:
                v = names->get(op_arg);
                w = locals->get(v);
                if (w != Universe::HiNone) {
                    PUSH(w);
                    break;
                }

                PUSH(Universe::HiNone);
                break;

            case ByteCode::STORE_NAME:
                v = names->get(op_arg);
                locals->put(v, POP());
                break;

            case ByteCode::PRINT_ITEM:
                v = POP();
                v->print();
                break;

            case ByteCode::PRINT_NEWLINE:
                printf("\n");
                break;

            case ByteCode::BINARY_ADD:
                v = POP();
                w = POP();
                PUSH(w->add(v));
                break;

            case ByteCode::RETURN_VALUE:
                POP();
                break;

            case ByteCode::COMPARE_OP:
                w = POP();
                v = POP();

                switch(op_arg) {
                case ByteCode::GREATER:
                    PUSH(v->greater(w));
                    break;

                case ByteCode::LESS:
                    PUSH(v->less(w));
                    break;

                case ByteCode::EQUAL:
                    PUSH(v->equal(w));
                    break;

                case ByteCode::NOT_EQUAL:
                    PUSH(v->not_equal(w));
                    break;

                case ByteCode::GREATER_EQUAL:
                    PUSH(v->ge(w));
                    break;
               
                case ByteCode::LESS_EQUAL: 
                    PUSH(v->le(w));
                    break;

                default:
                    printf("Error: Unrecognized compare op %d\n", op_arg);

                }
                break;

            case ByteCode::POP_JUMP_IF_FALSE:
                v = POP();
                if (v == Universe::HiFalse)
                    pc = op_arg;
                break;

            case ByteCode::JUMP_FORWARD:
                pc += op_arg;
                break;

            case ByteCode::JUMP_ABSOLUTE:
                pc = op_arg;
                break;

            case ByteCode::SETUP_LOOP:
                _loop_stack->add(new Block(
                    op_code, pc + op_arg,
                    STACK_LEVEL()));
                break;

            case ByteCode::POP_BLOCK:
                b = _loop_stack->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                break;

            case ByteCode::BREAK_LOOP:
                b = _loop_stack->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                pc = b->_target;
                break;

            default:
                printf("Error: Unrecognized byte code %d\n", op_code);
        }
    }
}

