/**
 * A logger provides writing on terminal - and once the game has been closed, also in a file -
 * everything that happens during gaming: resource loading, settings loading, errors ecc...
 * 
 * Since it oughta write the messagges on a file, it needs an instance of fstream.
 * Any errors about the creating of this file cannot be written on it, just since it could not be created; then, FilesUtils 
 * cannot be integrated within this class. 
 * 
 * Althought that, functions about load the files are gonna be copied by FilesUtils' ones and edited a bit;
 * 
 * @date 2022-08-01
 * @copyright Copyright (c) 2022
 * @author Gabriele-P03
 */

#ifndef LOGGER_JPL
#define LOGGER_JPL

    #ifdef __linux__
        #include <libgen.h> //For dirname()
        #include <unistd.h> //For readlink()
        #include <linux/limits.h> //For MAX_PATH
    #elif defined(_WIN32)
        #include <windows.h>
    #endif



    namespace jpl{

        namespace _logger{

            typedef const char* LOG_STATUS;

            //No errors occurred
            extern const LOG_STATUS OK;
            //Warning message
            extern const LOG_STATUS WARNING;
            //Error message. Program may be closed
            extern const LOG_STATUS ERR;

        }
    }

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

namespace jpl{

    namespace _logger{
    
        class Logger{

            private:
                /**
                 * Return the standard representation of the path to the logger's file
                 * path_to_your_project/logs/getFileNameOfInstancce()
                 * 
                 * @return std::string 
                 */
                static std::string getStandardPathToFile();

            protected:

                //Return the file name of today e.g. dd-mm-yyyy_hh-mm-ss.txt
                static std::string getFileNameOfInstance();

                static inline std::tm* getTM(){
                    std::time_t now = std::time(0);
                    
                    return std::localtime(&now);
                }

                std::fstream* file;

                
            public:

                /**
                 * Create a new instance of Logger associated with the output file at the given path
                 * 
                 * @param pathToFile 
                 */
                Logger(std::string pathToFile);

                static Logger* INSTANCE;

                /**
                 * Print on terminal @msg
                 * Write on file the @msg and flushes it.
                 * It is implicit an ok status
                 * @param msg 
                 */
                void print(std::string msg);

                /**
                 * Print on terminal @msg
                 * Write on file the @msg and flushes it.
                 * It is implicit a log status
                 * @param msg 
                 */
                void print(std::string msg, LOG_STATUS status);

                /**
                 * Close file of printing
                 */
                void closeLogger();

                ~Logger();
        };

    }

} 

#endif