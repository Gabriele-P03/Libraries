/**
 * @file
 * 
 * A JSONKeyNotFoundException is thrown whenever a name-based getter is invoked and no fields 
 * had been found
 * 
 * @date 2023-04-22
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef JSON_KEY_NOT_FOUND_EXCEPTION_JPL
#define JSON_KEY_NOT_FOUND_EXCEPTION_JPL

#include "JSONException.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{
            namespace _exception{
        
                class JSONKeyNotFoundException : public JSONException{
                    
                    public:

                        JSONKeyNotFoundException(std::string msg) : JSONException("JSONKeyNotFoundException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        JSONKeyNotFoundException() : JSONKeyNotFoundException(""){}

                };
            }
        }
    }
}

#endif