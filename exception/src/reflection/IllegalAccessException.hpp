/**
 * @file
 * 
 * An IllegalAccessException is thrown whenever a non-public field is attempted to be get via reflexpr TS
 * or any other kind of reflection feature that will be implemented later in C++.
 * 
 * Since reflexpr TS is experimental this exception could seem as useless, indeed it is though for a later feature.
 * 
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef ILLEGAL_ACCESS_EXCEPTION_JPL
#define ILLEGAL_ACCESS_EXCEPTION_JPL

#include "../AbstractException.hpp"


namespace jpl{

    namespace _exception{

        class IllegalAccessException : public AbstractException{

            private:

                /**
                 * It is the private field name which caused the exception
                 */
                const char* _cause;
            
            public:

                IllegalAccessException(const char* const _cause, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("IllegalAccessException", msg, file_name, function_name, line), _cause(_cause){}

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
 * @param object the non-public field
 */
#define IllegalAccessException(object) jpl::_exception::IllegalAccessException(STRINGIFY(object), "",  __FILENAME__, __func__, __LINE__)


#endif