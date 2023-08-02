/**
 * @file
 * 
 * An IOException is thrown when an error is occurred in runtime during an I/O operation either on a socket or a file
 * 
 * @date 2023-08-01
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef IO_EXCEPTION_JPL
#define IO_EXCEPTION_JPL

#include "RuntimeException.hpp"
#include <jpl/utils/debug/ErrorUtils.hpp>

namespace jpl{

    namespace _exception{

        class IOException : public RuntimeException{

            protected:
                const unsigned int error_code;
                std::string description; 

            public:
                IOException(unsigned int error_code, std::string description, std::string msg) : RuntimeException("IOException", msg), error_code(error_code), description(description){}
                IOException(unsigned int error_code, std::string description) : IOException(error_code, description, ""){}
                IOException(unsigned int error_code) : IOException(error_code, _utils::_error::_GetLastErrorAsString(error_code), ""){}
                IOException(std::string msg) : IOException(_utils::_error::_GetLastError()){this->msg = msg;}
                IOException() : IOException(_utils::_error::_GetLastError()){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = this->type_ex;
                    buffer += " Error Code: ";
                    buffer += std::to_string(this->error_code);
                    buffer += " -> ";
                    buffer += this->description;
                    buffer += " ";
                    buffer += this->msg;

                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    c_buffer[buffer.size()] = '\0';
                    return c_buffer;
                }
        };
    }
}

#endif