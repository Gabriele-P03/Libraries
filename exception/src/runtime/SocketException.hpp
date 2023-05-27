/**
 * A SocketException is thrown whenever a socket error is occurred in runtime.
 * 
 * Since a socket can be assimilated into every process which has been initialized via open(), this exception can be used
 * even for socket which are not stricly used as a networking purpose 
 * 
 * @file 
 * 
 * @date 2023-05-27
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef SOCKET_EXCEPTION_HPP
#define SOCKET_EXCEPTION_HPP

#include "RuntimeException.hpp"
#include <jpl/utils/ErrorUtils.hpp>

namespace jpl{

    namespace _exception{

        class SocketException : public RuntimeException{

            protected:

                /**
                 * The occurred error's code
                 */
                const unsigned int error_code;
                /**
                 * The file descriptor of the socket which has caused this exception
                 */
                const unsigned int fd;

                /**
                 * It is used to let destructor know if it has to delete msg field
                 * 
                 * If the construcor with only either error_code or none parameters is called, the msg which describes 
                 * the error occurred is retrieved via ErrorUtils, which return an std::string, but Exception module 
                 * uses const char* for it, then an std::string#c_str must be called on Errorutils#_GetLastErrorAsString(unsigned int),
                 * but since that string will be deleted just after the call, we need to store as an "independent" field
                 */
                bool deleteMSG;

            public:
                SocketException(const unsigned int fd, const unsigned int error_code, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    RuntimeException("SocketException", msg, file_name, function_name, line), error_code(error_code), fd(fd){
                    
                    this->deleteMSG = false;
                }
                
                SocketException(const unsigned int fd, const unsigned int error_code, const char* file_name, const char* function_name, const int line) : 
                    SocketException(fd, error_code, "", file_name, function_name, line){

                    std::string msg_s = jpl::_utils::_error::_GetLastErrorAsString(this->error_code); 
                    this->msg = new char[msg_s.size()];
                    memcpy((char*)this->msg, msg_s.c_str(), msg_s.size());
                    this->deleteMSG = true;
                }
       
                inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +  
                                                     ": FD("       + std::to_string(this->fd) + 
                                                     ") Code("     + std::to_string(this->error_code) + 
                                                     ") -> " + std::string(this->msg);


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }

                ~SocketException(){
                    if(this->deleteMSG){
                        delete[] this->msg;
                    }
                }
        };
    }
}

#define SocketException3(fd, error_code, msg) jpl::_exception::SocketException(fd, error_code, msg, __FILENAME__, __func__, __LINE__)
#define SocketException2(fd, error_code) jpl::_exception::SocketException(fd, error_code,  __FILENAME__, __func__, __LINE__)
#define SocketException1(fd) SocketException2(fd, jpl::_utils::_error::_GetLastError())

#define GET_SOCKET_EXCEPTION_CONSTRUCTOR_MACRO_JPL(_1, _2, _3,NAME, ...) NAME

/**
 * @brief error_code may be automagically fetched by ErrorUtils#_GetLastError() and msg by ErrorUtils#_GetLastErrorAsString(unsigned int)
 * 
 * @param fd file descriptor of the socket
 * @param error_code (OPTIONAL) error code
 * @param msg (OPTIONAL) message which describe error_code
 */
#define SocketException(...) GET_SOCKET_EXCEPTION_CONSTRUCTOR_MACRO_JPL(__VA_ARGS__, SocketException3, SocketException2, SocketException1)(__VA_ARGS__)


#endif