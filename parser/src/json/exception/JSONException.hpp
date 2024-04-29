/**
 * @file
 * 
 * A JSONException is the base exception class of any exception thrown by JSON Parser.
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef JSON_EXCEPTION_JPL
#define JSON_EXCEPTION_JPL

#include <jpl/exception/runtime/RuntimeException.hpp>

namespace jpl{
    namespace _parser{
        namespace _json{
            namespace _exception{
        
                class JSONException : public jpl::_exception::RuntimeException{
                    
                    public:

                        JSONException(std::string name, std::string msg) : jpl::_exception::RuntimeException(name, msg){
                            if( typeid(this) == typeid(JSONException) ){
                                #ifdef AUTO_LOG_EXCEPTION_JPL
                                    _logger::error(this->getStacktraceAsString());
                                #endif
                            }
                        }

                };
            }
        }
    }
}

#endif