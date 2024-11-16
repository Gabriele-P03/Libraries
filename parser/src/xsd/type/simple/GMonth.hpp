/**
 * @file
 * 
 * A gmonth type
 * 
 * @author Gabriele-P03
 */
#ifndef GMONTH_TYPE_XSD_JPL
#define GMONTH_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class GMonth : public AbstractType{
                    
                    protected:
                        ~GMonth(){}

                    public:
                        GMonth() : AbstractType("GMONTH"){}
                        static const GMonth* const GMONTH;
                };

            }
        }
    }
}

#endif