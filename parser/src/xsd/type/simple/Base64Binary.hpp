/**
 * @file
 * 
 * A base64binary type
 * 
 * @author Gabriele-P03
 */
#ifndef BASE64BINARY_TYPE_XSD_JPL
#define BASE64BINARY_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Base64Binary : public AbstractType{
                    
                    protected:
                        ~Base64Binary(){}

                    public:
                        Base64Binary() : AbstractType("BASE64BINARY"){}
                        static const Base64Binary* const BASE64BINARY;
                };

            }
        }
    }
}

#endif