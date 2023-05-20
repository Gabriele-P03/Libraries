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

            public:
                RuntimeException(const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("RuntimeException", msg, file_name, function_name, line){}

        };
    }
}

/**
 * @param msg describer message
 * 
 */
#define RuntimeException(msg) jpl::_exception::RuntimeException(msg, __FILENAME__, __func__, __LINE__)

#endif