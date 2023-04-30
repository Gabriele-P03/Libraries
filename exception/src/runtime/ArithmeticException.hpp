/**
 * An ArithmeticException is thrown whenever an invalid operation is attempted on a wrong math value;
 * for instance, value/0
 * 
 * As explained in AbstractException's documentation, altough constructors are declared as public, you should avoid to call them.
 * It can be thrown by constructor with 2 parameters (as you can see by the macro defined at the end of this file)
 *
 * In this exception what() is overriden in order to print the field which is illegal.
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef ARITHMETIC_EXCEPTION_JPL
#define ARITHMETIC_EXCEPTION_JPL

#include "../AbstractException.hpp"


namespace jpl{

    namespace _exception{

        class ArithmeticException : public AbstractException{

            private:

                const char* _cause;
            
            public:

                ArithmeticException(const char* const _cause, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("ArithmeticException", msg, file_name, function_name, line), _cause(_cause){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) + 
                                                     " " + std::string(this->msg) + "\n";


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }
        };
    }
}


#define STRINGIFY(arg) #arg
#define ArithmeticException(object, msg) jpl::_exception::ArithmeticException(STRINGIFY(object), msg,  __FILENAME__, __func__, __LINE__)


#endif