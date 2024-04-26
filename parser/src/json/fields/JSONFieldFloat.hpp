#ifndef JSON_FIELD_FLOAT_JPL
#define JSON_FIELD_FLOAT_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldFloat : public JSONField{

                protected:
                    float value;
                
                public:
                    JSONFieldFloat(std::string name, unsigned long tabs, float value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldFloat(std::string name, unsigned long tabs) : JSONFieldFloat(name, tabs, 0){}
                    JSONFieldFloat(std::string name) : JSONFieldFloat(name, 0){}
                    JSONFieldFloat() : JSONFieldFloat(""){}

                    float getFloat() const noexcept{return this->value;}
                    void setFloat(float value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldFloat r){return this->value = r.value;}
            };
        }
    }
}

#endif