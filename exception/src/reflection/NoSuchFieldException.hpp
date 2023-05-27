/**
 * @file
 * 
 * A NoSuchFieldException is thrown whenever a field which had been attempted to be get via reflexpr TS
 * or any other kind of reflection feature that will be implemented later in C++, has not been found.
 * 
 * Since reflexpr TS is experimental this exception could seem as useless, indeed it is though for a later feature.
 * 
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef NO_SUCH_FIELD_EXCEPTION_JPL
#define NO_SUCH_FIELD_EXCEPTION_JPL

#include "../AbstractException.hpp"


namespace jpl{

    namespace _exception{

        class NoSuchFieldException : public AbstractException{

            private:

                /**
                 * It is the field which caused the exception
                 */
                const char* _cause;
                /**
                 * It is the class which _cause had been looking for into
                 */
                const char* _class_name;
            
            public:

                NoSuchFieldException(const char* const _cause, const char* _class_name, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    AbstractException("NoSuchFieldException", msg, file_name, function_name, line), _cause(_cause), _class_name(_class_name){}

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +
                                                     ": there's no "   + std::string(this->_cause) + 
                                                     " into "       + std::string(this->_class_name) + "\0";


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }
        };
    }
}



/**
 * @brief object will be stringified
 * @brief class will be stringified
 * 
 * @param object the field which had been looking for
 * @param class the class where the field had been looking for into
 */
#define NoSuchFieldException(object, class) jpl::_exception::NoSuchFieldException(STRINGIFY(object), STRINGIFY(class), "",  __FILENAME__, __func__, __LINE__)


#endif