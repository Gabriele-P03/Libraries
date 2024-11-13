/**
 * @file
 * 
 * An DTDNotFoundException is thrown whenever an either Element or Attribute name-based getter is invoked and no fields 
 * had been found
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef DTD_NOT_FOUND_EXCEPTION_JPL
#define DTD_NOT_FOUND_EXCEPTION_JPL

#include "DTDException.hpp"

namespace jpl{
    namespace _parser{
        namespace _dtd{
            namespace _exception{
        
                class DTDNotFoundException : public DTDException{
                    
                    public:

                        DTDNotFoundException(std::string msg) : DTDException("DTDNotFoundException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        DTDNotFoundException() : DTDNotFoundException(""){}

                };
            }
        }
    }
}

#endif