#ifndef JSON_FIELD_UINT_JPL
#define JSON_FIELD_UINT_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldUInt : public JSONField{

                protected:
                    unsigned int value;
                
                public:
                    JSONFieldUInt(std::string name, unsigned long tabs, unsigned int value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldUInt(std::string name, unsigned long tabs) : JSONFieldUInt(name, tabs, 0){}
                    JSONFieldUInt(std::string name) : JSONFieldUInt(name, 0){}
                    JSONFieldUInt() : JSONFieldUInt(""){}

                    unsigned int getUInt() const noexcept{return this->value;}
                    void setUInt(unsigned int value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldUInt r){return this->value = r.value;}

                    std::string toString() const noexcept override{
                        return std::string(this->tabs, '\t') + (!this->name.empty() ? "\"" + this->name + "\": " : "") + std::to_string(this->value);
                    }
            };
        }
    }
}

#endif