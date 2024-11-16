/**
 * @file
 * 
 * A anyuri type
 * 
 * @author Gabriele-P03
 */
#ifndef ANYURI_TYPE_XSD_JPL
#define ANYURI_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class AnyURI : public AbstractType{
                    
                    protected:
                        ~AnyURI(){}

                    public:
                        AnyURI() : AbstractType("ANYURI"){}
                        static const AnyURI* const ANYURI;
                };

            }
        }
    }
}

#endif