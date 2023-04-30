/**
 * A NullPointerException is thrown whenever an operation had been attempted on a nullptr pointer
 * or NULL field.
 * 
 * As explained into AbstractException's documentation, altough constructors are declared as public, you should avoid to call them.
 * it can be thrown by macro-constructor with 2 parameters (as you can see at the end of this file)
 * 
 * In this exception what() is overriden in order to print the field which is illegal.
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef NULL_POINTER_EXCEPTION_JPL
#define NULL_POINTER_EXCEPTION_JPL

#include "../AbstractException.hpp"


namespace jpl{

    namespace _exception{

        class NullPointerException : public AbstractException{

            private:

                const char* _cause;
            
            public:

                NullPointerException(const char* const _cause, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("NullPointerException", msg, file_name, function_name, line), _cause(_cause){}

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


#define STRINGIFY(arg) #arg
/**
 * @brief object will be stringified
 * 
 * @param object the null field 
 * @param msg describer message
 */
#define NullPointerException(object, msg) jpl::_exception::NullPointerException(STRINGIFY(object), msg,  __FILENAME__, __func__, __LINE__)


#endif