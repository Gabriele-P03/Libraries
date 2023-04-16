/**
 * An IllegalArgumentException is thrown whenever an invalid parameter is passed to a function
 * 
 * @date 2023-04-16
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ILLEGAL_ARGUMENT_EXCEPTION_JPL
#define ILLEGAL_ARGUMENT_EXCEPTION_JPL

#include <exception>

namespace jpl{

    namespace _exception{

        class IllegalArgumentException : protected std::exception{

            private:
                const char* msg;
            
            public:
                IllegalArgumentException(const char* msg){this->msg = msg;}
                IllegalArgumentException() : IllegalArgumentException(""){}

                const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    return this->msg;
                }

                //operator <<
        };
    }
}

#endif