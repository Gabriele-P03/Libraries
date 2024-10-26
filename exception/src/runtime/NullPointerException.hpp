/**
 * @file
 * 
 * A NullPointerException is thrown whenever an operation had been attempted on a nullptr pointer
 * or NULL field.
 * 
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef NULL_POINTER_EXCEPTION_JPL
#define NULL_POINTER_EXCEPTION_JPL

#include "RuntimeException.hpp"


namespace jpl{

    namespace _exception{

        class NullPointerException : public RuntimeException{

            
            public:
                NullPointerException(const std::string &msg) : RuntimeException("NullPointerException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                NullPointerException() : NullPointerException(""){}

                NullPointerException(const NullPointerException &a) : RuntimeException(a){}

                NullPointerException& operator= (const NullPointerException& a){
                    RuntimeException::operator=(a);
                }
                
                ~NullPointerException() {}

        };
    }
}

#endif