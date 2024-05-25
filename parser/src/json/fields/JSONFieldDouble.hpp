#ifndef JSON_FIELD_DOUBLE_JPL
#define JSON_FIELD_DOUBLE_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldDouble : public JSONField{

                protected:
                    double value;
                
                public:
                    JSONFieldDouble(std::string name, unsigned long tabs, double value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldDouble(std::string name, unsigned long tabs) : JSONFieldDouble(name, tabs, 0){}
                    JSONFieldDouble(std::string name) : JSONFieldDouble(name, 0){}
                    JSONFieldDouble() : JSONFieldDouble(""){}

                    double getDouble() const noexcept{return this->value;}
                    void setDouble(double value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldDouble r){return this->value = r.value;}

                    std::string toString() const noexcept override{
                        return (!this->name.empty() ? "\"" + this->name + "\": " : "") + std::to_string(this->value);
                    }
            };
        }
    }
}

#endif