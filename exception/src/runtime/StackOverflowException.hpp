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

            private:

                /**
                 * The name of the list which caused this exception
                 */
                const char* _cause;

            public:
                StackOverflowException(const char* _object, const char* msg, const char* file_name, const char* function_name, const unsigned int line) :
                    RuntimeException("StackOverflowException", "", file_name, function_name, line), _cause(_object){
                }

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
 * @param object the full list
 */
#define StackOverflowException(object) StackOverflowException(STRINGIFY(object), "", __FILENAME__, __func__, __LINE__)

#endif