/**
 * @file
 * 
 * A RuntimeException is thrown when an error is occurred in runtime but its cause cannot be enstabilished 
 * 
 * @date 2023-04-30
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef RUNTIME_EXCEPTION_JPL
#define RUNTIME_EXCEPTION_JPL

#include "../AbstractException.hpp"

namespace jpl{

    namespace _exception{

        class RuntimeException : public AbstractException{

            protected:
                RuntimeException(std::string type_ex, std::string msg, unsigned long skip) : AbstractException(type_ex, msg, skip+1){}
                RuntimeException(std::string type_ex, std::string msg) : AbstractException(type_ex, msg, 2){} //2 skips

            public:
                RuntimeException(std::string msg) : RuntimeException("RuntimeException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                        ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                RuntimeException() : RuntimeException(""){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                        ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }

        };
    }
}

#endif