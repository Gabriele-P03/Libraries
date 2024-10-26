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

            public:

                NoSuchFieldException(const std::string &msg) : AbstractException("ArithmeticException", msg){
                    #ifdef AUTO_LOG_EXCEPTION_JPL
                         ::jpl::_logger::error(AbstractException::getStacktraceAsString());
                    #endif
                }
                NoSuchFieldException() : NoSuchFieldException(""){}

                NoSuchFieldException(const NoSuchMethodException &a) : AbstractException(a){}

                NoSuchFieldException& operator= (const NoSuchFieldException& a){
                    AbstractException::operator=(a);
                    return *this;
                }
                
                ~NoSuchFieldException() {}
        };
    }
}

#endif