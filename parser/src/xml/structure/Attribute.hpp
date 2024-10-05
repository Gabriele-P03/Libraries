/**
 * 
 * @file
 * 
 * The rappresentation of an XML element's attribute.
 * It does respect XML syntax about attribute's name 
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */

#ifndef XML_ATTRIBUTE_JPL
#define XML_ATTRIBUTE_JPL

#include <string>
#include "../exception/XMLParsingException.hpp"
#include <jpl/exception/runtime/IllegalArgumentException.hpp>

namespace jpl{
    
    namespace _parser{
        
        namespace _xml{

            struct Attribute{
                private:

                    std::string name;
                    std::string attribute;

                public:
                    Attribute(std::string name, std::string attribute){
                        validateName(name);
                        this->name = name;
                        this->attribute = attribute;
                    }

                    std::string getName() const noexcept { return this->name;}
                    void setName(std::string name){
                        validateName(name);
                        this->name = name;
                    }
                    
                    std::string getAttribute() const noexcept { return this->attribute;}
                    void setAttribute(std::string attribute) noexcept {
                        this->attribute = attribute;
                    }

                    /**
                     * @return the representation of an attribute as XML requires (name='value')
                     */
                    std::string toString() const noexcept{return this->name + "='" + this->attribute + "'";}
            };
        }
    }
}



#endif