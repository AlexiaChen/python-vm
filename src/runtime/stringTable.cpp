#include "runtime/stringTable.hpp"
#include "object/hiString.hpp"

StringTable* StringTable::instance = NULL;

StringTable* StringTable::get_instance() {
    if (instance == NULL)
        instance = new StringTable();

    return instance;
}

StringTable::StringTable() {
    next_str = new HiString("next");
    mod_str  = new HiString("__module__");
    init_str = new HiString("__init__");
    add_str  = new HiString("__add__");
    len_str  = new HiString("__len__");
}

