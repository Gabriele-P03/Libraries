/**
 * @file
 * 
 * A StackOverflow exception is thrown whenever an addition of an element into a stack is attempted 
 * but the capacity of the LIFO structure does not permit it
 * 
 * @date 2023-04-23
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef STACKOVERFLOW_EXCEPTION_JPL
#define STACKOVERFLOW_EXCEPTION_JPL

#include "RuntimeException.hpp"

namespace jpl{

    namespace _exception{

        class StackOverflowException : public RuntimeException{


            public:
                StackOverflowException(const std::string &msg) :RuntimeException("StackOverflowException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                StackOverflowException() :StackOverflowException(""){}

                StackOverflowException(const StackUnderflowException &a) : RuntimeException(a){}

                StackOverflowException& operator= (const StackOverflowException& a){
                    RuntimeException::operator=(a);
                    return *this;
                }
                
                ~StackOverflowException() {}

        };
    }
}


#endif