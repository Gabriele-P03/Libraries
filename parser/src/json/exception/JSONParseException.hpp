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
#ifndef JSON_PARSE_EXCEPTION_JPL
#define JSON_PARSE_EXCEPTION_JPL

#include "JSONException.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{
            namespace _exception{
        
                class JSONParseException : public JSONException{
                    
                    public:

                        JSONParseException(std::string msg) : JSONException("JSONParseException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        JSONParseException() : JSONParseException(""){}

                };
            }
        }
    }
}

#endif