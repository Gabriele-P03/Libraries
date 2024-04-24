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
#include <ctime>
#include <variant>

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONField{
                
                protected:
                    unsigned long tabs; //Count how many tabs. They will be used for indentation 
                    std::string name;

                public:
                    JSONField(std::string name, unsigned long tabs){
                        this->name = name;
                        this->tabs = tabs;
                    }
                    JSONField(std::string name) : JSONField(name, 0){}
                    JSONField() : JSONField(""){}

                    std::string getName() const noexcept {return this->name;}
                    unsigned long getTabsCount() const noexcept {return this->tabs;}
                    void setName(std::string name) noexcept {this->name = name;}
                    void setTabsCount(unsigned long tabs) noexcept {this->tabs = tabs;}
            };

        }
    }
}

#endif