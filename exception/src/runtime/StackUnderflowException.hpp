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

#include "../AbstractException.hpp"

namespace jpl{

    namespace _exception{

        class StackUnderflowException : public AbstractException{

            private:

                /**
                 * The name of the list which caused this exception
                 */
                const char* _cause;

            public:
                StackUnderflowException(const char* _object, const char* msg, const char* file_name, const char* function_name, const unsigned int line) :
                    AbstractException("StackUnderflowException", msg, file_name, function_name, line), _cause(_object){
                    
                    std::string buffer = std::string(_object) + " " + std::string(msg);
                    this->msg = new char[buffer.size()];
                    char* tmp = (char*)&msg[0];
                    memcpy(tmp, buffer.c_str(), buffer.size());
                }

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) + "\n";

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