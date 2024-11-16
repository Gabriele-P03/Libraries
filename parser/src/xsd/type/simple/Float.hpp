/**
 * @file
 * 
 * A float type
 * 
 * @author Gabriele-P03
 */
#ifndef FLOAT_TYPE_XSD_JPL
#define FLOAT_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Float : public AbstractType{
                    
                    protected:
                        ~Float(){}

                    public:
                        Float() : AbstractType("FLOAT"){}
                        static const Float* const FLOAT;
                };

            }
        }
    }
}

#endif