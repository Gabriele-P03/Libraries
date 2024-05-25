#ifndef JSON_FIELD_LONG_JPL
#define JSON_FIELD_LONG_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldLong : public JSONField{

                protected:
                    long value;
                
                public:
                    JSONFieldLong(std::string name, unsigned long tabs, long value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldLong(std::string name, unsigned long tabs) : JSONFieldLong(name, tabs, 0){}
                    JSONFieldLong(std::string name) : JSONFieldLong(name, 0){}
                    JSONFieldLong() : JSONFieldLong(""){}

                    long getLong() const noexcept{return this->value;}
                    void setLong(long value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldLong r){return this->value = r.value;}

                    std::string toString() const noexcept override{
                        return std::string(this->tabs, '\t') + (!this->name.empty() ? "\"" + this->name + "\": " : "") + std::to_string(this->value);
                    }
            };
        }
    }
}

#endif