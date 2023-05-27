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

            private:

                /**
                 * name of the file wich could not be found
                 */
                const char* _cause;
            
            public:

                FileNotFoundException(const char* const _cause, const char* file_name, const char* function_name, const int line) : 
                    RuntimeException("FileNotFoundException", "", file_name, function_name, line), _cause(_cause){}

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
 * @param file name of the file attempted to get 
 */
#define FileNotFoundException(file) jpl::_exception::FileNotFoundException(file,  __FILENAME__, __func__, __LINE__)


#endif