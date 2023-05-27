/**
 * @file
 * A logger provides writing log-program on terminal and even on a file
 *  
 * If OI_LOGGER_JPL macro is defined, an Optional Induction is performed with this module.
 * An OI with this Logger will not let your program exit with a FAILURE_STATUS whenever it has not
 * been able to create a log file
 * 
 * CUSTOM_LOGGER_JPL definition will not delegate the creation of the static instance (INSTANCE) to Logger.
 * It will be your duty to define it later, but be carefull since JPL module use INSTANCE instance to print stuff.
 *
 * If any call to jpl:_logger::Logger#print() will be done before have defined INSTANCE, the message will be only print on terminal
 * but will not be written on file
 * 
 * Therefore, if you wanna use your own instance of this class and you do not need to print any errors of other module,
 * you could opt to define only CUSTOM_LOGGER_JPL
 *   
 * The usage of CUSTOM_LOGGER_JPL and OI_LOGGER_JPL is available 
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

    namespace jpl{

        namespace _logger{

            typedef const char* const LOG_STATUS;
            extern LOG_STATUS INFO, WARNING, ERROR, DEBUG;

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
                     * Is is used to check, when OMI_LOGGER_JPL macro is defined, if logger
                     * is able to write on the file the message, too 
                     */
                    bool flag;
                    
                public:

                    /**
                     * Create a new instance of Logger associated with the output file at the given path
                     * 
                     * @param pathToFile aboslute path of the file which is wanted to be used as output one
                     */
                    Logger(std::string pathToFile){
                        this->file = new std::fstream();
                        this->file->open(pathToFile, std::ios_base::out);
                        
                        this->flag = false;

                        if(file->fail()){
                            #ifndef OI_LOGGER_JPL   
                                this->print("Logger File could not be created and OI is not performed. Exiting...", jpl::_logger::ERROR);                       
                                exit(EXIT_FAILURE);   
                            #else
                                this->print("Logger File could not be created but OI has been performed. Log file will not be written", jpl::_logger::WARNING);
                            #endif
                        }else{
                            this->flag = true;
                        }
                    }

                    #ifndef CUSTOM_LOGGER_JPL
                        static Logger* INSTANCE;
                    #endif

                    /**
                     * Print on terminal msg
                     * Write on file the msg and flushes it.
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
                    void print(std::string msg, const LOG_STATUS status);

                    /**
                     * Close file of printing
                     */
                    void closeLogger();

                    /**
                     * @brief this check-function is useless to call unless you have defined
                     * OI_LOGGER_JPL 
                     * 
                     * @return if Logger is writing on file, too
                     */
                    inline bool isWriting(){ return this->flag; }

                    ~Logger() noexcept(false);
            };
        }
    } 

#endif