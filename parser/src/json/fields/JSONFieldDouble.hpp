#ifndef JSON_FIELD_DOUBLE_JPL
#define JSON_FIELD_DOUBLE_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldDoule : public JSONField{

                protected:
                    double value;
                
                public:
                    JSONFieldDoule(std::string name, unsigned long tabs, double value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldDoule(std::string name, unsigned long tabs) : JSONFieldDoule(name, tabs, 0){}
                    JSONFieldDoule(std::string name) : JSONFieldDoule(name, 0){}
                    JSONFieldDoule() : JSONFieldDoule(""){}

                    double getDouble() const noexcept{return this->value;}
                    void setDouble(double value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldDoule r){return this->value = r.value;}
            };
        }
    }
}

#endif