/**
 * @file
 * 
 * A datetime type
 * 
 * @author Gabriele-P03
 */
#ifndef DATETIME_TYPE_XSD_JPL
#define DATETIME_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class DateTime : public AbstractType{
                    
                    protected:
                        ~DateTime(){}

                    public:
                        DateTime() : AbstractType("DATETIME"){}
                        static const DateTime* const DATETIME;
                };

            }
        }
    }
}

#endif