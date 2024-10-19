/**
 * @file
 * 
 * A CSVException is the base exception class of any exception thrown by CSV Parser.
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef CSV_EXCEPTION_JPL
#define CSV_EXCEPTION_JPL

#include <jpl/exception/runtime/RuntimeException.hpp>

namespace jpl{
    namespace _parser{
        namespace _csv{
            namespace _exception{
        
                class CSVException : public jpl::_exception::RuntimeException{
                    
                    public:

                        CSVException(std::string name, std::string msg) : jpl::_exception::RuntimeException(name, msg){
                            if( typeid(this) == typeid(CSVException) ){
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