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
                std::string cast_attempted;
                /**
                 * The class supplied
                 */
                std::string cast_needed;
            
            public:

                IllegalCastException(const std::string &cast_attempted, const std::string &cast_needed, const std::string &msg) : 
                    RuntimeException("IllegalCastException", msg), cast_attempted(cast_attempted), cast_needed(cast_needed){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                    }
                IllegalCastException(const std::string &cast_attempted, const std::string &cast_needed) : IllegalCastException(cast_attempted, cast_needed, ""){}
                IllegalCastException(const std::string &msg) : IllegalCastException("UNKNOWN" ,"UNKNOWN", msg){}
                IllegalCastException() : IllegalCastException(""){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " Attempted Cast: " + std::string(this->_cast_attempted) +
                                                     " Required Cast: " + std::string(this->_cast_needed) + 
                                                     " " + std::string(this->msg);

                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }


                IllegalCastException(const IllegalCastException &a) : RuntimeException(a){
                    this->cast_needed = a.cast_needed;
                    this->cast_attempted = a.cast_attempted;
                }

                IllegalCastException& operator= (const IllegalCastException& a){
                    RuntimeException::operator=(a);
                    this->cast_needed = a.cast_needed;
                    this->cast_attempted = a.cast_attempted;
                    return *this;
                }
                
                ~IllegalCastException() {}
        };
    }
}

#endif