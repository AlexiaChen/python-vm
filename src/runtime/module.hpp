#ifndef MODULE_OBJECT_HPP
#define MODULE_OBJECT_HPP

#include "object/hiObject.hpp"

class HiDict;

class ModuleKlass : public Klass {
private:
    static ModuleKlass* _instance;
    ModuleKlass();

public:
    static ModuleKlass* get_instance();
    void initialize();
};

class ModuleObject : public HiObject {
private:
    HiString*   _mod_name;
 
public:
    ModuleObject(HiDict* x);
    static ModuleObject* import_module(HiObject* mod_name);

    void put(HiObject* x, HiObject* y);
    HiObject* get(HiObject* x);
};

#endif
