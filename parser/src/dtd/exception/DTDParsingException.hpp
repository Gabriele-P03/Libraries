/**
 * @file
 * 
 * An DTDParsingException is thrown whenever an either attribute or element of an DTD file is ill-formed
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef DTD_PARSING_EXCEPTION_JPL
#define DTD_PARSING_EXCEPTION_JPL

#include "DTDException.hpp"

namespace jpl{
    namespace _parser{
        namespace _dtd{
            namespace _exception{
        
                class DTDParsingException : public DTDException{
                    
                    public:

                        DTDParsingException(std::string msg) : DTDException("DTDParsingException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        DTDParsingException() : DTDParsingException(""){}

                };
            }
        }
    }
}

#endif