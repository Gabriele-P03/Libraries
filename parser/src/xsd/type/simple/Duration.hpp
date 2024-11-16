/**
 * @file
 * 
 * A duration type
 * 
 * @author Gabriele-P03
 */
#ifndef DURATION_TYPE_XSD_JPL
#define DURATION_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Duration : public AbstractType{
                    
                    protected:
                        ~Duration(){}

                    public:
                        Duration() : AbstractType("DURATION"){}
                        static const Duration* const DURATION;
                };

            }
        }
    }
}

#endif