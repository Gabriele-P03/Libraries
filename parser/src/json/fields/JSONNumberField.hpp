

/**
 * Json Array abstraction
 * 
 *
 * @file JSONObject.hpp
 * @author Gabriele-P03
 */

#ifndef JSON_NUMBER_FIELD_JPL
#define JSON_NUMBER_FIELD_JPL

#include "JSONField.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONNumberField : public JSONField<long>{

                public:
                    JSONNumberField(std::string name, unsigned long tabs, long value) : JSONField(name, tabs, value){}
                    JSONNumberField(std::string name, long value) : JSONNumberField(name, 0, value){}
                    JSONNumberField(std::string name) : JSONField(name){}
                    JSONNumberField() : JSONField(){}

                    template<>
                    virtual long getValue() const noexcept override{
                        return this->value;
                    }
                    virtual void setValue(long value) noexcept override{
                        this->value = value;
                    }
            };
        }
    }
}

#endif