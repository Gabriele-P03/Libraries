#ifndef JSON_FIELD_INT_JPL
#define JSON_FIELD_INT_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONFieldInt : public JSONField{

                protected:
                    int value;
                
                public:
                    JSONFieldInt(std::string name, unsigned long tabs, int value) : JSONField(name, tabs){
                        this->value = value;
                    }
                    JSONFieldInt(std::string name, unsigned long tabs) : JSONFieldInt(name, tabs, 0){}
                    JSONFieldInt(std::string name) : JSONFieldInt(name, 0){}
                    JSONFieldInt() : JSONFieldInt(""){}

                    int getInt() const noexcept{return this->value;}
                    void setInt(int value) noexcept {this->value = value;}

                    inline bool operator==(const JSONFieldInt r){return this->value = r.value;}
            };
        }
    }
}

#endif