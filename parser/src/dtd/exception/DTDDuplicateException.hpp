/**
 * @file
 * 
 * An DTDDuplicateException is thrown whenever a duplicate attribute is found for an element
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef DTD_DUPLICATE_EXCEPTION_JPL
#define DTD_DUPLICATE_EXCEPTION_JPL

#include "DTDException.hpp"

namespace jpl{
    namespace _parser{
        namespace _dtd{
            namespace _exception{
        
                class DTDDuplicateException : public DTDException{
                    
                    public:

                        DTDDuplicateException(std::string msg) : DTDException("DTDDuplicateException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        DTDDuplicateException() : DTDDuplicateException(""){}

                };
            }
        }
    }
}

#endif