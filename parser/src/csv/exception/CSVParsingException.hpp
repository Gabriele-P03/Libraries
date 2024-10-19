/**
 * @file
 * 
 * A CSVParsingException is thrown whenever a CSV line could not be parsed due to any reason
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef CSV_PARSING_EXCEPTION_JPL
#define CSV_PARSING_EXCEPTION_JPL

#include "CSVException.hpp"

namespace jpl{
    namespace _parser{
        namespace _csv{
            namespace _exception{
        
                class CSVParsingException : public CSVException{
                    
                    public:

                        CSVParsingException(std::string msg) : CSVException("CSVParsingException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        CSVParsingException() : CSVParsingException(""){}

                };
            }
        }
    }
}

#endif