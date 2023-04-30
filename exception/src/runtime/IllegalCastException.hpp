/**
 * An IllegalCastException is thrown whenever an invalid cast on an object is attempted
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
#ifndef ILLEGAL_CAST_EXCEPTION_JPL
#define ILLEGAL_CAST_EXCEPTION_JPL

#include "../AbstractException.hpp"


namespace jpl{

    namespace _exception{

        class IllegalCastException : public AbstractException{

            private:

                const char* _cast_attempted;
                const char* _cast_needed;
                const char* _cause;
            
            public:

                IllegalCastException(const char* const _cause, const char* _cast_attempted, const char* _cast_needed, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("IllegalCastException", msg, file_name, function_name, line), _cause(_cause), _cast_attempted(_cast_attempted), _cast_needed(_cast_needed){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) + 
                                                     ". Attempted Cast: " + std::string(this->_cast_attempted) +
                                                     ". Required Cast: " + std::string(this->_cast_needed) + "\n";


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }
        };
    }
}


#define STRINGIFY(arg) #arg
#define IllegalCastException(object, cast_attempted, cast_needed) jpl::_exception::IllegalCastException(STRINGIFY(object), STRINGIFY(cast_attempted), STRINGIFY(cast_needed), "",  __FILENAME__, __func__, __LINE__)


#endif