/**
 * @file
 * 
 * An IllegalArgumentException is thrown whenever a wrong argument is passed to 
 * any type of function (method, constructor...) 
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef ILLEGAL_ARGUMENT_EXCEPTION_JPL
#define ILLEGAL_ARGUMENT_EXCEPTION_JPL

#include "RuntimeException.hpp"


namespace jpl{

    namespace _exception{

        class IllegalArgumentException : public RuntimeException{

            private:

                /**
                 * Field name of the illegal argument
                 */
                const char* _cause;

                //Since an IllegalArgument can be thrown by IndexOutOfBounds
                friend class IndexOutOfBoundsException;
            
            public:

                IllegalArgumentException(const char* const _cause, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    RuntimeException("IllegalArgumentException", msg, file_name, function_name, line), _cause(_cause){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) +   
                                                     " "          + std::string(this->msg) + "\0";


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }
        };
    }
}




/**
 * @brief arg will be stringified
 * 
 * @param arg the field which is illegal
 * @param msg describer message
 */
#define IllegalArgumentException(arg, msg) jpl::_exception::IllegalArgumentException(STRINGIFY(arg), msg,  __FILENAME__, __func__, __LINE__)


#endif