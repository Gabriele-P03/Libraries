#ifndef JSON_FIELD_TM_JPL
#define JSON_FIELD_TM_JPL

#include "JSONField.hpp"
#include <ctime>

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldTM : public JSONField{

                protected:
                    std::tm value;
                
                public:
                    JSONFieldTM(std::string name, unsigned long tabs, std::tm value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldTM(std::string name, unsigned long tabs) : JSONFieldTM(name, tabs, std::tm{}){}
                    JSONFieldTM(std::string name) : JSONFieldTM(name, 0){}
                    JSONFieldTM() : JSONFieldTM(""){}

                    std::tm getTM() const noexcept{return this->value;}
                    void setTM(std::tm value) noexcept {this->value = value;}

                    //inline bool operator==(const JSONFieldTM r){return this->value == r.value;}

                    std::string toString() const noexcept override{
                        return (!this->name.empty() ? "\"" + this->name + "\": " : "") + std::to_string(this->value);
                    }
            };
        }
    }
}

#endif