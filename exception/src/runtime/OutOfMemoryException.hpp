/**
 * @file
 * 
 * An OutOfMemory exception can be thrown when a program has not enough memory available in order to instance
 * new objects
 * 
 * @date 2023-04-23
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef OUTOFMEMORY_EXCEPTION_JPL
#define OUTOFMEMORY_EXCEPTION_JPL

#include "RuntimeException.hpp"

namespace jpl{

    namespace _exception{

        class OutOfMemoryException : public RuntimeException{

            private:

                /**
                 * The name of the object which caused this exception
                 */
                const char* _cause;

            public:
                OutOfMemoryException(const char* _object, const char* msg, const char* file_name, const char* function_name, const unsigned int line) :
                    RuntimeException("OutOfMemoryException", msg, file_name, function_name, line), _cause(_object){
                }

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) + 
                                                     " "    + std::string(this->msg) + "\0";

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
#define OutOfMemoryException(object, msg) OutOfMemoryException(STRINGIFY(object), msg, __FILENAME__, __func__, __LINE__)

#endif