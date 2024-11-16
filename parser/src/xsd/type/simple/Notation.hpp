/**
 * @file
 * 
 * A notation type
 * 
 * @author Gabriele-P03
 */
#ifndef NOTATION_TYPE_XSD_JPL
#define NOTATION_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class Notation : public AbstractType{
                    
                    protected:
                        ~Notation(){}

                    public:
                        Notation() : AbstractType("NOTATION"){}
                        static const Notation* const NOTATION;
                };

            }
        }
    }
}

#endif