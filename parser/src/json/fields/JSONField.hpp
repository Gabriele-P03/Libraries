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
#include <type_traits>

namespace jpl{
    namespace _parser{
        namespace _json{

            //A JsonField can only be composed by either a primitive type or an std::string
            template <typename T>
            concept PrimitiveType = std::__or_<std::is_fundamental<T>::value, std::is_same<T, std::string>::value>;  

            template <PrimitiveType T>
            class JSONField{
                
                protected:
                    unsigned long tabs; //Count how many tabs. They will be used for indentation 
                    std::string name;
                    T value;

                public:
                    JSONField(std::string name, unsigned long tabs, T value);
                    JSONField(std::string name, T value);
                    JSONField(std::string name);
                    JSONField();

                    virtual T getValue() const noexcept;
                    virtual std::string getName() const noexcept;
                    virtual unsigned long getTabsCount() const noexcept;

                    virtual void setValue(T value) noexcept;
                    virtual void setName(std::string name) noexcept;
                    virtual void setTabsCount(unsigned long tabs) noexcept;
            };
        }
    }
}

#endif