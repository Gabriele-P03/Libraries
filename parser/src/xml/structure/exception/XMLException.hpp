/**
 * @file
 * 
 * A XMLException is the base exception class of any exception thrown by XML Parser.
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef XML_EXCEPTION_JPL
#define XML_EXCEPTION_JPL

#include <jpl/exception/runtime/RuntimeException.hpp>

namespace jpl{
    namespace _parser{
        namespace _xml{
            namespace _exception{
        
                class XMLException : public jpl::_exception::RuntimeException{
                    
                    public:

                        XMLException(std::string name, std::string msg) : jpl::_exception::RuntimeException(name, msg){
                            if( typeid(this) == typeid(XMLException) ){
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