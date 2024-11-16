/**
 * @file
 * 
 * @author Gabriele-P03
 */

#ifndef ABSTRACT_TYPE_XSD_JPL
#define ABSTRACT_TYPE_XSD_JPL

#include <string>

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class AbstractType{

                    protected:
                        const std::string name;
                        AbstractType(const std::string &namme) : name(name){} 
                        ~AbstractType(){}
                    public:
                           
                        const std::string& getName() const noexcept{return this->name;}
                };
            }
        }
    }
}

#endif