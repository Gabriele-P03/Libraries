/**
 * @file
 * 
 * A gyear type
 * 
 * @author Gabriele-P03
 */
#ifndef GYEAR_TYPE_XSD_JPL
#define GYEAR_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class GYear : public AbstractType{
                    
                    protected:
                        ~GYear(){}

                    public:
                        GYear() : AbstractType("GYEAR"){}
                        static const GYear* const GYEAR;
                };

            }
        }
    }
}

#endif