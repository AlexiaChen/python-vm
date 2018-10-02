#ifndef HANDLES_HPP
#define HANDLES_HPP

class HiObject;
class OopClosure;

class Handle {
    HiObject* _value;
    Handle*   _next;

public:
    Handle(HiObject* t);
    ~Handle();

    void oops_do(OopClosure* f);
    HiObject* operator ->();
    HiObject* resolve();
};

class HandleMark {
friend class Handle;
private:
    static HandleMark* instance;
    Handle* _head;

public:
    HandleMark();

    static HandleMark* get_instance();
    void oops_do(OopClosure* f);
};

#endif
