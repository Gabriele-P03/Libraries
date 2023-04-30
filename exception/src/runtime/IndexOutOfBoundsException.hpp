/**
 * An IndexOutOfBounds exception is thrown whenever a substraction of an element out from a stack is attempted 
 * but it is already empty
 * 
 * As explained into AbstractException's documentation, altough constructors are declared as public, you should avoid to call them.
 * it can be thrown by macro-constructor with 3 parameters (as you can see at the end of this file)
 * 
 * In this exception what() is overriden in order to print the fielde which are illegal.
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

        class IndexOutOfBoundsException : public AbstractException{

            private:
                const char* _object;
                const unsigned int max, attempted;

                void catchIllegalMaxAttempted(){
                    if(this->max >= this->attempted){
                        throw new IllegalArgumentException(o, "cannot be thrown with a MAX greater than ATTEMPTED");
                    }else{
                        std::string buffer =            std::string(this->type_ex) + 
                                                        " thrown by " + std::string(this->function_name) + 
                                                        " at line "   + std::to_string(this->line) + 
                                                        " of "        + std::string(this->file_name) +
                                                        ": "          + std::string(this->_object) + 
                                                        ". Index "    + std::to_string(this->attempted) +   
                                                        " attempted against max available as "          + std::to_string(this->max) + "\n";


                        this->msg = new char[buffer.size()];
                        char* tmp = (char*)&msg[0];
                        memcpy(tmp, buffer.c_str(), buffer.size());
                    }
                }

            public:

                /**
                 * Create a new IndexOutOfBoundsException
                 * 
                 * @param max size of the object
                 * @param attempted current index attempted to insert at
                 * @throw 
                 */
                IndexOutOfBoundsException(const char* _object, const unsigned int max, const unsigned int attempted, const char* file_name, const char* function_name, const unsigned int line) :
                    AbstractException("IndexOutOfBoundsException", "", file_name, function_name, line), max(max), attempted(attempted), _object(_object){

                    try{
                        this->catchIllegalMaxAttempted();
                    }catch(const IllegalArgumentException* ex){
                        std::string buffer =            std::string(this->type_ex) + 
                                                        " thrown by " + std::string(this->function_name) + 
                                                        " at line "   + std::to_string(this->line) + 
                                                        " of "        + std::string(this->file_name) + 
                                                        " could not be evaluated due to an internal IllegalArgumentException: Max is greater than Attempted\n";


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
 * @param max size of object
 * @param attempted the index attempted
 * 
 */
#define IndexOutOfBoundsException(object, max, attempted) jpl::_exception::IndexOutOfBoundsException(STRINGIFY(object), max, attempted, __FILENAME__, __func__, __LINE__)

#endif