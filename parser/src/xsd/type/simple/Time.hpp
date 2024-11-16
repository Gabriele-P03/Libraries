/**
 * @file
 * 
 * A time type
 * 
 * @author Gabriele-P03
 */
#ifndef TIME_TYPE_XSD_JPL
#define TIME_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Time : public AbstractType{
                    
                    protected:
                        ~Time(){}

                    public:
                        Time() : AbstractType("TIME"){}
                        static const Time* const TIME;
                };

            }
        }
    }
}

#endif