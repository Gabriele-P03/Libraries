/**
 * @file
 * 
 * An IndexOutOfBounds exception is thrown whenever getting an element whose index is out-of-range of a list is attempted.
 * It throws an IllegalArgumentException if Max is greater than Attempted
 * 
 * 
 * @date 2023-04-23
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_JPL
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_JPL

#include "IllegalArgumentException.hpp"

namespace jpl{

    namespace _exception{

        class IndexOutOfBoundsException : public RuntimeException{

            private:
                /**
                 * the list which the operation had been performed on
                 */
                const char* _object;
                /**
                 * size of list
                 */
                const unsigned int max;
                /**
                 * the index attempted
                 */
                const unsigned int attempted;

                void catchIllegalMaxAttempted(){
                    if(this->max > this->attempted){
                        throw new IllegalArgumentException(o, "cannot be thrown with a MAX greater than ATTEMPTED");
                    }else{
                        std::string buffer =            std::string(this->type_ex) + 
                                                        " thrown by " + std::string(this->function_name) + 
                                                        " at line "   + std::to_string(this->line) + 
                                                        " of "        + std::string(this->file_name) +
                                                        ": "          + std::string(this->_object) + 
                                                        ". Index "    + std::to_string(this->attempted) +   
                                                        " attempted against max available as "          + std::to_string(this->max) + "\0";


                        this->msg = new char[buffer.size()];
                        char* tmp = (char*)&msg[0];
                        memcpy(tmp, buffer.c_str(), buffer.size());
                    }
                }

            public:
                IndexOutOfBoundsException(const char* _object, const unsigned int max, const unsigned int attempted, const char* file_name, const char* function_name, const unsigned int line) :
                    RuntimeException("IndexOutOfBoundsException", "", file_name, function_name, line), max(max), attempted(attempted), _object(_object){

                    try{
                        this->catchIllegalMaxAttempted();
                    }catch(const IllegalArgumentException* ex){
                        std::string buffer =            std::string(this->type_ex) + 
                                                        " thrown by " + std::string(this->function_name) + 
                                                        " at line "   + std::to_string(this->line) + 
                                                        " of "        + std::string(this->file_name) + 
                                                        " could not be evaluated due to an internal IllegalArgumentException: Max is greater than Attempted\0";


                        this->msg = new char[buffer.size()];
                        char* tmp = (char*)&msg[0];
                        memcpy(tmp, buffer.c_str(), buffer.size());
                    }
                }

                inline const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    return this->msg;
                }
        };
    }
}

/**
 * @brief object will be stringified
 * 
 * @param object the list which the operation had been performed on
 * @param max size of list
 * @param attempted the index attempted
 * 
 * @throw IllegalArgumentException if max is greater or equal than attempted
 */
#define IndexOutOfBoundsException(object, max, attempted) jpl::_exception::IndexOutOfBoundsException(STRINGIFY(object), max, attempted, __FILENAME__, __func__, __LINE__)

#endif