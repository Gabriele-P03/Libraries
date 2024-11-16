/**
 * @file
 * 
 * A gday type
 * 
 * @author Gabriele-P03
 */
#ifndef GDAY_TYPE_XSD_JPL
#define GDAY_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class GDay : public AbstractType{
                    
                    protected:
                        ~GDay(){}

                    public:
                        GDay() : AbstractType("GDAY"){}
                        static const GDay* const GDAY;
                };

            }
        }
    }
}

#endif