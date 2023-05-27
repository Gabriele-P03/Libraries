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

            private:

                /**
                 * The name of the list which caused this exception
                 */
                const char* _cause;

            public:
                StackUnderflowException(const char* _object, const char* msg, const char* file_name, const char* function_name, const unsigned int line) :
                    RuntimeException("StackUnderflowException", msg, file_name, function_name, line), _cause(_object){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) + "\0";

                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }
        };
    }
}

/**
 * @brief object will be stringified
 * 
 * @param object the empty list 
 */
#define StackUnderflowException(object) StackUnderflowException(STROMGIFY(object), "", __FILENAME__, __func__, __LINE__)

#endif