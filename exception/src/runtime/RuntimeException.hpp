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
                RuntimeException(const char* type_ex, const char* msg, const char* file_name, const char* function_name, const int line) :
                    AbstractException(type_ex, msg, file_name, function_name, line){}
                RuntimeException(const char* msg, const char* file_name, const char* function_name, const int line) : 
                    RuntimeException("RuntimeException", msg, file_name, function_name, line){}

        };
    }
}

/**
 * @param msg describer message
 * 
 */
#define RuntimeException1(msg) jpl::_exception::RuntimeException(msg, __FILENAME__, __func__, __LINE__)
#define RuntimeException2(type_ex, msg) jpl::_exception::RuntimeException(type_ex, msg, __FILENAME__, __func__, __LINE__)
#define RuntimeException3(type_ex, msg, file) jpl::_exception::RuntimeException(type_ex, msg, file, __func__, __LINE__)
#define RuntimeException4(type_ex, msg, file, func) jpl::_exception::RuntimeException(type_ex, msg, file, func, __LINE__)
#define RuntimeException5(type_ex, msg, file, func, line) jpl::_exception::RuntimeException(type_ex, msg, file, func, line)

#define GET_RUNTIME_EXCEPTION_CONSTRUCTOR_MACRO_JPL(_1,_2,_3,_4,_5,NAME,...) NAME
#define RuntimeException(...) GET_RUNTIME_EXCEPTION_CONSTRUCTOR_MACRO_JPL(__VA_ARGS__,RuntimeException5,RuntimeException4,RuntimeException3,RuntimeException2,RuntimeException1)(__VA_ARGS__)

#endif