/**
 * @file
 * 
 * A hexbinary type
 * 
 * @author Gabriele-P03
 */
#ifndef HEXBINARY_TYPE_XSD_JPL
#define HEXBINARY_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class HexBinary : public AbstractType{
                    
                    protected:
                        ~HexBinary(){}

                    public:
                        HexBinary() : AbstractType("HEXBINARY"){}
                        static const HexBinary* const HEXBINARY;
                };

            }
        }
    }
}

#endif