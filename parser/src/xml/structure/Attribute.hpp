/**
 * 
 * @file
 * 
 * The rappresentation of an XML element's attribute
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
                    const std::string name;
                    const std::string attribute;

                public:
                    Attribute(std::string name, std::string attribute) : name(name), attribute(attribute){
                        if(this->name.empty())
                            throw new jpl::_exception::IllegalArgumentException("An XML Attribute cannot have an empty name");
                        if(this->name.find(" ") != std::string::npos)
                            throw new jpl::_parser::_xml::_exception::XMLParsingException("XML Attribute name cannot contains empty space: " + this->name);
                    }

                    std::string getName() const noexcept { return this->name;}
                    std::string getAttribute() const noexcept { return this->attribute;}

                    std::string toString() const noexcept{return this->name + "='" + this->attribute + "'";}
            };
        }
    }
}



#endif