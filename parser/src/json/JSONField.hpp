/**
 * Json Array abstraction
 * 
 *
 * @file JSONObject.hpp
 * @author Gabriele-P03
 */

#ifndef JSON_FIELD_JPL
#define JSON_FIELD_JPL

#include <string>

namespace jpl{
    namespace _parser{
        namespace _json{

            template <typename T>
            class JSONField{
                
                protected:
                    unsigned long tabs; //Count how many tabs. They will be used for indentation 
                    std::string name;
                    T value;

                public:
                    JSONField(std::string name, unsigned long tabs, T value);
                    JSONField(std::string name, T value);
                    JSONField(T value);
                    JSONField();
            };
        }
    }
}

#endif