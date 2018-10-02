#include "util/handles.hpp"
#include "memory/oopClosure.hpp"

HandleMark* HandleMark::instance = new HandleMark();

HandleMark::HandleMark() {
    _head = 0x0;
}

HandleMark* HandleMark::get_instance() {
    return instance;
}

void HandleMark::oops_do(OopClosure* f) {
    if (_head)
        _head->oops_do(f);
}

Handle::Handle(HiObject* t) {
    _value = t;

    _next = HandleMark::instance->_head;
    HandleMark::instance->_head = this;
}

Handle::~Handle() {
    _value = 0x0;
    
    HandleMark::instance->_head = _next;
    _next = 0x0;
}

HiObject* Handle::operator ->() {
    return _value;
}

void Handle::oops_do(OopClosure* f) {
    f->do_oop(&_value);
}

HiObject* Handle::resolve() {
    return _value;
}

