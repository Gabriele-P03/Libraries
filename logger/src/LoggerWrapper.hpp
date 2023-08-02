#ifndef LOGGER_WRAPPER_JPL
#define LOGGER_WRAPPER_JPL

    #ifdef USE_LOGGER_JPL
        #include "Logger.hpp"
    #else 

        #include <iostream>
        #include <string>
        #include <ctime>

        namespace jpl{

            namespace _logger{

                static std::string getTM(){
                    std::time_t now = std::time(0);
                    std::tm *ltm = std::localtime(&now);

                    return  std::to_string((*ltm).tm_mday) + "-" + 
                            std::to_string((*ltm).tm_mon+1) + "-" + 
                            std::to_string((*ltm).tm_year + 1900) + "_" +
                            std::to_string((*ltm).tm_hour) + ":" +
                            std::to_string((*ltm).tm_min) + ":" +
                            std::to_string((*ltm).tm_sec);
                }

                void print(std::string msg){std::cout<<getTM()<<msg<<std::endl;}
            }
        } 
    #endif

#endif