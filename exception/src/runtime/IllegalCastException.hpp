/**
 * @file
 * 
 * An IllegalCastException is thrown whenever an invalid cast on an object is attempted
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef ILLEGAL_CAST_EXCEPTION_JPL
#define ILLEGAL_CAST_EXCEPTION_JPL

#include "RuntimeException.hpp"


namespace jpl{

    namespace _exception{

        class IllegalCastException : public RuntimeException{

            private:

                /**
                 * The class which the field has been attempted to be cast to
                 */
                const char* _cast_attempted;
                /**
                 * The class supplied
                 */
                const char* _cast_needed;
                /**
                 * The field casted
                 */
                const char* _cause;
            
            public:

                IllegalCastException(const char* const _cause, const char* _cast_attempted, const char* _cast_needed, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    RuntimeException("IllegalCastException", msg, file_name, function_name, line), _cause(_cause), _cast_attempted(_cast_attempted), _cast_needed(_cast_needed){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": "   + std::string(this->_cause) + 
                                                     ". Attempted Cast: " + std::string(this->_cast_attempted) +
                                                     ". Required Cast: " + std::string(this->_cast_needed) + "\0";


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }
        };
    }
}


/**
 * @brief object will be stringified
 * @brief cast_attempted will be stringified
 * @brief cast_needed will be stringified
 * 
 * @param object the field attempted to be cast
 * @param cast_needed the class supplied
 * @param cast_attempted the class which the field has been attempted to be cast to
 */
#define IllegalCastException(object, cast_attempted, cast_needed) jpl::_exception::IllegalCastException(STRINGIFY(object), STRINGIFY(cast_attempted), STRINGIFY(cast_needed), "",  __FILENAME__, __func__, __LINE__)


#endif