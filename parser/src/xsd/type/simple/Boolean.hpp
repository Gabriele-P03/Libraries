/**
 * @file
 * 
 * A boolean type
 * 
 * @author Gabriele-P03
 */
#ifndef BOOLEAN_TYPE_XSD_JPL
#define BOOLEAN_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Boolean : public AbstractType{
                    
                    protected:
                        ~Boolean(){}

                    public:
                        Boolean() : AbstractType("BOOLEAN"){}
                        static const Boolean* const BOOLEAN;
                };

            }
        }
    }
}

#endif