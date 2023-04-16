/**
 * Here some functions about printing on the logger are defined
 * 
 * If this header has been included after have defined USE_LOGGER_JPL macro, the logger of the jpl framework will be used.
 * 
 * If you have already included this header with the definition of the macro which had been talked about above, but now you need to print with cout
 * always in the same program, you just need to undefine that macro before include it. Just remember to re-define it after you have included 
 * this header or whenever it is needed again.
 * 
 * Type of message is defined into Logger.hpp, but they're used by cout, too. 
 * If the first time you have included this header, you have not used the USE_LOGGER_JPL macro, an internal definion of LOG_STATUs are done.
 * Do not take care about re-definition of them if you have included later it with the macro defined, ODR is done 
 * 
 * @date 2023-02-04
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef PRINT_LOGGER_JPL
#define PRINT_LOGGER_JPL

    #ifdef USE_LOGGER_JPL 

        #include "Logger.hpp"

    #else

        namespace jpl{
            namespace _logger{
                typedef const char* LOG_STATUS;

                //No errors occurred
                const LOG_STATUS OK = "OK";
                //Warning message
                const LOG_STATUS WARNING = "WARNING";
                //Error message. Program may be closed
                const LOG_STATUS ERR = "ERROR";
            }
        }

    #endif

    #include <iostream>
    #include <string>

    namespace jpl{

        inline void print(std::string msg, jpl::_logger::LOG_STATUS type_msg){

            #ifdef USE_LOGGER_JPL
                jpl::_logger::Logger::INSTANCE->print(msg, type_msg);
            #else
                std::cout<<std::string(type_msg)<<": "<<msg<<std::endl;
            #endif

        } 
        
        inline void print(std::string msg){
            #ifdef USE_LOGGER_JPL
                jpl::_logger::Logger::INSTANCE->print(msg, jpl::_logger::OK);
            #else
                std::cout<<std::string(jpl::_logger::OK)<<": "<<msg<<std::endl;
            #endif
        }

    }

#endif