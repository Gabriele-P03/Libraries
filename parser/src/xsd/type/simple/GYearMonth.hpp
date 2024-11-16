/**
 * @file
 * 
 * A gyearmonth type
 * 
 * @author Gabriele-P03
 */
#ifndef GYEARMONTH_TYPE_XSD_JPL
#define GYEARMONTH_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class GYearMonth : public AbstractType{
                    
                    protected:
                        ~GYearMonth(){}

                    public:
                        GYearMonth() : AbstractType("GYEARMONTH"){}
                        static const GYearMonth* const GYEARMONTH;
                };

            }
        }
    }
}

#endif