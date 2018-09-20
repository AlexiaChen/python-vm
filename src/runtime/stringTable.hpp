#ifndef STRING_TABLE_HPP
#define STRING_TABLE_HPP

class HiString;
class OopClosure;

class StringTable {
private:
    static StringTable* instance;
    StringTable();

public:
    static StringTable* get_instance();
    
    HiString* next_str;
    HiString* mod_str;
    HiString* init_str;
};

#endif

