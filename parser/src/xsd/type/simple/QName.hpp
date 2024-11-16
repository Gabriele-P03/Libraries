/**
 * @file
 * 
 * A qname type
 * 
 * @author Gabriele-P03
 */
#ifndef QNAME_TYPE_XSD_JPL
#define QNAME_TYPE_XSD_JPL

#include "../AbstractType.hpp"

namespace jpl{
    namespace _parser{
        namespace _xsd{
            namespace _type{

                class QName : public AbstractType{
                    
                    protected:
                        ~QName(){}

                    public:
                        QName() : AbstractType("QNAME"){}
                        static const QName* const QNAME;
                };

            }
        }
    }
}

#endif