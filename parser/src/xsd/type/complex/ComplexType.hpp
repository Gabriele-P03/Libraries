/**
 * @file
 * 
 * A complex type is an XSD element type created by user
 * 
 * @author Gabriele-P03
 */
#ifndef COMPLEX_TYPE_XSD_JPL
#define COMPLEX_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class ComplexType : public AbstractType{
                    
                    protected:
                        ~ComplexType(){}

                    public:
                        ComplexType() : AbstractType("COMPLEX_TYPE"){}
                        static const ComplexType* const COMPLEX_TYPE;
                };

            }
        }
    }
}

#endif