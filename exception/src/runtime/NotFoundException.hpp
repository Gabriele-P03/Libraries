/**
 * @file
 * 
 * A NotFoundException is thrown whenever a field has not been found into a list of objects.
 * 
 * This exception is a bit Runtime. There are some extended version of it  
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef NOT_FOUND_EXCEPTION_JPL
#define NOT_FOUND_EXCEPTION_JPL

#include "RuntimeException.hpp"

namespace jpl{

    namespace _exception{

        class NotFoundException : public RuntimeException{

            private:

                /**
                 * The object which has not been found
                 */
                const char* _cause;
            
            public:

                NotFoundException(const char* const _cause, const char* file_name, const char* function_name, const int line) : 
                    RuntimeException("NotFoundException", "", file_name, function_name, line), _cause(_cause){}

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
 * @param object object attempted to get 
 */
#define NotFoundException(object) jpl::_exception::NotFoundException(STRINGIFY(object),  __FILENAME__, __func__, __LINE__)


#endif