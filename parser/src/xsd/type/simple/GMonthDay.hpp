/**
 * @file
 * 
 * A gmonthday type
 * 
 * @author Gabriele-P03
 */
#ifndef GMONTHDAY_TYPE_XSD_JPL
#define GMONTHDAY_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class GMonthDay : public AbstractType{
                    
                    protected:
                        ~GMonthDay(){}

                    public:
                        GMonthDay() : AbstractType("GMONTHDAY"){}
                        static const GMonthDay* const GMONTHDAY;
                };

            }
        }
    }
}

#endif