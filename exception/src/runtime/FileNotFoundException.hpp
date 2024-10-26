/**
 * @file
 * 
 * A FileNotFoundException is thrown whenever a file has not been found.
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef FILE_NOT_FOUND_EXCEPTION_JPL
#define FILE_NOT_FOUND_EXCEPTION_JPL

#include "RuntimeException.hpp"


namespace jpl{

    namespace _exception{

        class FileNotFoundException : public RuntimeException{

            
            public:

                FileNotFoundException(const std::string &msg) : RuntimeException("FileNotFoundException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                FileNotFoundException() : FileNotFoundException(""){}

                FileNotFoundException(const FileNotFoundException &a) : RuntimeException(a){}

                FileNotFoundException& operator= (const FileNotFoundException& a){
                    RuntimeException::operator=(a);
                    return *this;
                }
                
                ~FileNotFoundException() {}
        };
    }
}

#endif