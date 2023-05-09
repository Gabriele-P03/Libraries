/**
 * A FileNotFoundException is thrown whenever a file has not been found.
 * 
 * As explained into AbstractException's documentation, altough constructors are declared as public, you should avoid to call them.
 * it can be thrown by macro-constructor with 2 parameters (as you can see at the end of this file)
 * 
 * In this exception what() is overriden in order to print the field which is illegal.
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef FILE_NOT_FOUND_EXCEPTION_JPL
#define FILE_NOT_FOUND_EXCEPTION_JPL

#include "../AbstractException.hpp"


namespace jpl{

    namespace _exception{

        class FileNotFoundException : public AbstractException{

            private:

                const char* _cause;
            
            public:

                FileNotFoundException(const char* const _cause, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("FileNotFoundException", "", file_name, function_name, line), _cause(_cause){}

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


#define STRINGIFY(arg) #arg
/**
 * @brief object will be stringified
 * 
 * @param file file attempted to get 
 */
#define FileNotFoundException(file) jpl::_exception::FileNotFoundException(STRINGIFY(file),  __FILENAME__, __func__, __LINE__)


#endif