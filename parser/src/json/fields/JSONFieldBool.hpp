#ifndef JSON_FIELD_BOOL_JPL
#define JSON_FIELD_BOOL_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldBool : public JSONField{

                protected:
                    bool value;
                
                public:
                    JSONFieldBool(std::string name, unsigned long tabs, bool value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldBool(std::string name, unsigned long tabs) : JSONFieldBool(name, tabs, 0){}
                    JSONFieldBool(std::string name) : JSONFieldBool(name, 0){}
                    JSONFieldBool() : JSONFieldBool(""){}

                    bool getBool() const noexcept{return this->value;}
                    void setBool(bool value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldBool r){return this->value = r.value;}

                    std::string toString() const noexcept override{
                        return std::string(this->tabs, '\t') + (!this->name.empty() ? "\"" + this->name + "\": " : "") + (this->value ? "true" : "false"); 
                    }
            };
        }
    }
}

#endif