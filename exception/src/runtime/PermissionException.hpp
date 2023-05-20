/**
 * @file
 * 
 * A PermissionException is thrown whenever an error has been caused by a missed permission
 * 
 * @date 2023-05-20
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef PERMISSION_EXCEPTION_JPL
#define PERMISSION_EXCEPTION_JPL

#include "../AbstractException.hpp"

namespace jpl{

    namespace _exception{

        class PermissionException : public AbstractException{

            public:
                PermissionException(const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("RuntimeException", msg, file_name, function_name, line){}

        };
    }
}

/**
 * @param msg describer message
 * 
 */
#define PermissionException(msg) jpl::_exception::PermissionException(msg, __FILENAME__, __func__, __LINE__)


#endif