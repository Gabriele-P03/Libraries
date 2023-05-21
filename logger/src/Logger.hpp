/**
 * A logger provides writing log-program on terminal and in a file both.
 *  
 * 
 * If OMI_LOGGER_JPL macro is defined, an Optional 
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

    #include <string>
    #include <fstream>
    #include <iostream>
    #include <ctime>

    #include "FilesUtils.hpp"

    namespace jpl{

        namespace _logger{

            class Logger{

                protected:

                    //Return the file name of today e.g. dd-mm-yyyy_hh-mm-ss.txt
                    static std::string getFileNameOfInstance();

                    static inline std::tm* getTM(){
                        std::time_t now = std::time(0);
                        return std::localtime(&now);
                    }

                    std::fstream* file;

                    /**
                     * @brief If the fstream could be created, this flag is set to true,
                     * otherwise to false.
                     * Is is used to check, when OMI_LOGGER_JPL macro is defined, if logger
                     * is able to write on the file the message, too 
                     */
                    bool flag;
                    
                public:

                    /**
                     * Create a new instance of Logger associated with the output file at the given path
                     * 
                     * @param pathToFile 
                     */
                    Logger(std::string pathToFile){
                        this->file = new std::fstream();
                        this->file->open(pathToFile, std::ios_base::out);

                        if(!file){
                            #ifndef OMI_LOGGER_JPL                           
                                exit(EXIT_FAILURE);   
                            #else
                                this->flag = false;
                            #endif
                        }else{
                            this->flag = true;
                        }
                    }

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