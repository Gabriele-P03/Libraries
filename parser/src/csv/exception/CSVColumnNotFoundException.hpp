/**
 * @file
 * 
 * A CSVColumnNotFoundException is thrown whenever a column has not been found in table instance
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef CSV_COLUMN_NOT_FOUND_EXCEPTION_JPL
#define CSV_COLUMN_NOT_FOUND_EXCEPTION_JPL

#include "CSVException.hpp"

namespace jpl{
    namespace _parser{
        namespace _csv{
            namespace _exception{
        
                class CSVColumnNotFoundException : public CSVException{
                    
                    public:

                        CSVColumnNotFoundException(std::string msg) : CSVException("CSVColumnNotFoundException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        CSVColumnNotFoundException() : CSVColumnNotFoundException(""){}

                };
            }
        }
    }
}

#endif