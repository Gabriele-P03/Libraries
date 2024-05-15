/**
 * @file
 * 
 * An ArithmeticException is thrown whenever an invalid operation is attempted on a wrong math value;
 * for instance, value/0
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef ARITHMETIC_EXCEPTION_JPL
#define ARITHMETIC_EXCEPTION_JPL

#include "RuntimeException.hpp"


namespace jpl{

    namespace _exception{

        class ArithmeticException : public RuntimeException{

            private:
            
            public:

                ArithmeticException(std::string msg) : RuntimeException("ArithmeticException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                ArithmeticException() : ArithmeticException(""){}
        };
    }
}

#endif