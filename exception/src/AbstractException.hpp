/**
 * @file
 * 
 * An AbstractException is a template of a basic exception used by JPL to have theirs to be thrown.
 * 
 * @date 2023-04-16
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ABSTRACT_EXCEPTION_JPL
#define ABSTRACT_EXCEPTION_JPL

    #include <iostream>
    #include <vector>
    #include <string.h>

    #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
        #include <jpl/utils/debug/stacktrace/Stacktrace.hpp>
    #endif

    #ifdef AUTO_LOG_EXCEPTION_JPL
        #ifndef USE_STACKTRACE_W_EXCEPTION_JPL
            #error "Exception auto-logging is available only through  USE_STACKTRACE_W_EXCEPTION_JPL macro. Define it!"
        #endif
        #if !defined(LOGGER_WRAPPER_JPL) && !defined(LOGGER_JPL)
            #error "Either Logger or LoggerWrapper must be included before Exception if you wanna auto-log 'em"
        #endif 
        namespace jpl{
            namespace _logger{
                void error(std::string msg);
            }
        }
    #endif

    namespace jpl{

        namespace _exception{

            class AbstractException;


            class AbstractException : protected std::exception{

                protected:
                    
                    /**
                     * This is a description of the exception which has been thrown. It is passed by constructor
                     * and it is as the exception name
                     * 
                     */
                    std::string type_ex;

                    /**
                     * It is a description of what has just happened. For some exception it may be a template
                     * of stuff (usually when constructor does not need any msg)
                     */
                    std::string msg;   

                    #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                        _utils::_debug::Stacktrace* stacktrace;
                    #endif

                    AbstractException(std::string type_ex) : AbstractException(type_ex, ""){}
                    AbstractException(std::string type_ex, std::string msg) : type_ex(type_ex), msg(msg){
                        #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                            this->stacktrace = new _utils::_debug::Stacktrace(DEFAULT_SKIP_STACKFRAMES_JPL);
                        #endif
                    }
                    
                    
                public:
                    
                    /**
                     * @brief Print the type of the exception which has been thrown with the message that has been passed, too
                     * 
                     * @return const char* 
                     */
                    inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                        std::string buffer = 
                            std::string(this->type_ex) + ": " + std::string(this->msg);
                        char* c_buffer = new char[buffer.size()];
                        strcpy(c_buffer, buffer.c_str());
                        return c_buffer;
                    }

                    #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                        /**
                         * @return the Stacktrace of the thrown exception
                         */
                        virtual const _utils::_debug::Stacktrace* getStacktrace() const{return this->stacktrace;}

                        virtual const std::string getStacktraceAsString() const{

                            const char* tmp = this->what();
                            std::string buffer = std::string(tmp);
                            delete[] tmp;

                            for(unsigned int i = 0; i < this->stacktrace->getSize(); i++){
                                _utils::_debug::Frame frame = this->stacktrace->getFrameAt(i);
                                std::string tmp = "#" + std::to_string(i) + " Invalid Frame";
                                if(frame.frame_valid){
                                    tmp = "#" + std::to_string(i) + " " + frame.function_name + " of " + frame.file_name + " at line " + std::to_string(frame.line) + ". Address " + frame.address;
                                }
                                buffer += "\n\t" + tmp;
                            }

                            return buffer;
                        }
                    #endif

                    /**
                     * @brief 
                     * 
                     * @param os 
                     * @param iae 
                     * @return std::ostream& 
                     */
                    inline friend std::ostream& operator<<(std::ostream& os, const AbstractException &ex){

                        const char* buffer = ex.what();
                        os<<buffer<<std::endl;
                        delete[] buffer;

                        return os;
                    }
            };
        }
    }
#endif