/**
 * @file
 * 
 * A StackUnderflow exception is thrown whenever a substraction of an element out from a stack is attempted 
 * but it is already empty.
 * 
 * @date 2023-04-23
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef STACKUNDERFLOW_EXCEPTION_JPL
#define STACKUNDERFLOW_EXCEPTION_JPL

#include "RuntimeException.hpp"

namespace jpl{

    namespace _exception{

        class StackUnderflowException : public RuntimeException{

            public:
                StackUnderflowException(const std::string &msg) : RuntimeException("StackUnderflowException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                StackUnderflowException() : StackUnderflowException(""){}
        };
    }
}


#endif