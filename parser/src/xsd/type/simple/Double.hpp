/**
 * @file
 * 
 * A double type
 * 
 * @author Gabriele-P03
 */
#ifndef DOUBLE_TYPE_XSD_JPL
#define DOUBLE_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Double : public AbstractType{
                    
                    protected:
                        ~Double(){}

                    public:
                        Double() : AbstractType("DOUBLE"){}
                        static const Double* const DOUBLE;
                };

            }
        }
    }
}

#endif