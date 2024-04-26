#ifndef JSON_FIELD_ULONG_JPL
#define JSON_FIELD_ULONG_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldULong : public JSONField{

                protected:
                    unsigned long value;
                
                public:
                    JSONFieldULong(std::string name, unsigned long tabs, unsigned long value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldULong(std::string name, unsigned long tabs) : JSONFieldULong(name, tabs, 0){}
                    JSONFieldULong(std::string name) : JSONFieldULong(name, 0){}
                    JSONFieldULong() : JSONFieldULong(""){}

                    unsigned long getULong() const noexcept{return this->value;}
                    void setULong(unsigned long value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldULong r){return this->value = r.value;}
            };
        }
    }
}

#endif