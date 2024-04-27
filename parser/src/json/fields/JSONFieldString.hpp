#ifndef JSON_FIELD_STRING_JPL
#define JSON_FIELD_STRING_JPL

#include "JSONField.hpp"
#include <string>

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldString : public JSONField{

                protected:
                    std::string value;
                
                public:
                    JSONFieldString(std::string name, unsigned long tabs, std::string value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldString(std::string name, unsigned long tabs) : JSONFieldString(name, tabs, ""){}
                    JSONFieldString(std::string name) : JSONFieldString(name, 0){}
                    JSONFieldString() : JSONFieldString(""){}

                    std::string getString() const noexcept{return this->value;}
                    void setString(std::string value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldString r){return this->value.compare(r.value) == 0;}
            };
        }
    }
}

#endif