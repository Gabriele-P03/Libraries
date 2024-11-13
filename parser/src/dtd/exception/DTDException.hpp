/**
 * @file
 * 
 * A DTDException is the base exception class of any exception thrown by DTD Parser.
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef DTD_EXCEPTION_JPL
#define DTD_EXCEPTION_JPL

#include <jpl/exception/runtime/RuntimeException.hpp>

namespace jpl{
    namespace _parser{
        namespace _dtd{
            namespace _exception{
        
                class DTDException : public jpl::_exception::RuntimeException{
                    
                    public:

                        DTDException(std::string name, std::string msg) : jpl::_exception::RuntimeException(name, msg){
                            if( typeid(this) == typeid(DTDException) ){
                                #ifdef AUTO_LOG_EXCEPTION_JPL
                                    _logger::error(this->getStacktraceAsString());
                                #endif
                            }
                        }

                };
            }
        }
    }
}

#endif