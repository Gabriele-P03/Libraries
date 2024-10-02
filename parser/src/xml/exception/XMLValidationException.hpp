/**
 * @file
 * 
 * An XMLValidationException is thrown whenever a name of an attribute or element is not valid
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef XML_VALIDATIO_EXCEPTION_JPL
#define XML_VALIDATION_EXCEPTION_JPL

#include "XMLException.hpp"

namespace jpl{
    namespace _parser{
        namespace _xml{
            namespace _exception{
        
                class XMLValidationException : public XMLException{
                    
                    public:

                        XMLValidationException(std::string msg) : XMLException("XMLValidationException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        XMLValidationException() : XMLValidationException(""){}

                };
            }
        }
    }
}

#endif