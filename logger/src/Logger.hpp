/**
 * @file
 * A logger provides writing log-program on terminal and even on a file
 *  
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
    
    #include <jpl/utils/FilesUtils.hpp>
    #include <jpl/utils/debug/DebugUtils.hpp>

    namespace jpl{

        namespace _logger{
            
            typedef const char* const LOG_STATUS;
            /**
             * @brief Information message
             */
            extern LOG_STATUS INFO_JPL;
            /**
             * @brief Warning message
             */
            extern LOG_STATUS WARNING_JPL;
            /**
             * @brief Error message
             */
            extern LOG_STATUS ERROR_JPL;
            /**
             * @brief Debug message (not visible unless process has a debugger attached) 
             */
            extern LOG_STATUS DEBUG_JPL;

            class Logger{

                protected:

                    /**
                     * @return the file name of today e.g. dd-mm-yyyy_hh-mm-ss.txt
                     */
                    static std::string getFileNameOfInstance();

                    /**
                     * @return an instance of std::tm at the current moment
                     */
                    static inline std::tm* getTM(){
                        std::time_t now = std::time(0);
                        return std::localtime(&now);
                    }

                    /**
                     * Logger's output file
                     */
                    std::fstream* file;

                    /**
                     * @brief If the fstream could be created, this flag is set to true,
                     * otherwise to false.
                     * Is is used to check, when UFW_LOGGER_JPL macro is defined, if logger
                     * is able to write on file, too.
                     */
                    bool flag;
                    
                public:

                    /**
                     * Create a new instance of Logger associated with the output file at the given path.
                     * Quiet mode is implicitly set to false
                     * 
                     * @param pathToFile aboslute path of the file which is wanted to be used as output one
                     */
                    Logger(std::string pathToFile) : Logger(pathToFile, false){}

                    /**
                     * Create a new instance of Logger associated with the output file at the given path
                     * 
                     * @param pathToFile aboslute path of the file which is wanted to be used as output one
                     * @param quiet quiet mode 
                     */
                    Logger(std::string pathToFile, bool quiet){
                        
                        this->flag = false;

                        if(!quiet){
                            this->file = new std::fstream();
                            this->file->open(pathToFile, std::ios_base::out);

                            if(file->fail()){
                                #ifndef UFW_LOGGER_JPL   
                                    this->print("Logger File could not be created and OI is not performed. Exiting...", jpl::_logger::ERROR_JPL);                       
                                    exit(EXIT_FAILURE);   
                                #else
                                    this->print("Logger File could not be created but OI has been performed. Log file will not be written", jpl::_logger::WARNING);
                                #endif
                            }else{
                                this->flag = true;
                            }
                        }
                    }

                    #ifndef CUSTOM_LOGGER_JPL
                        static Logger* INSTANCE;
                    #endif

                    /**
                     * @brief Print msg on terminal
                     * Write msg on file and flushes it.
                     * 
                     * @param msg message
                     */
                    void print(std::string msg);

                    /**
                     * @brief write msg on terminal
                     * Write msg on file and flushes it.
                     * 
                     * @param msg message
                     * @param status status of the message
                     */
                    void print(std::string msg, const LOG_STATUS status);

                    /**
                     * Close logger and its file
                     */
                    void closeLogger();

                    /**
                     * @brief this check-function is useless to call unless you have defined
                     * UFW_LOGGER_JPL 
                     * 
                     * @return if Logger is able to write on file
                     */
                    inline bool isWriting(){ return this->flag; }

                    ~Logger();
            };
        }
    } 

#endif