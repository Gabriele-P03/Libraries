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
                            std::string(this->type_ex) + ": " + std::string(this->msg) + "\0";

                        #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                            const std::vector<_utils::_debug::Frame>* frames = this->stacktrace->getFrames();
                            for(unsigned int i = 0; i < frames->size(); i++){
                                _utils::_debug::Frame frame = frames->at(i);
                                std::string tmp = frame.function_name + " of " + frame.file_name + " at line " + std::to_string(frame.line) + ". Address " + frame.address;
                                buffer += "\n" + tmp;
                            }
                        #endif


                        char* c_buffer = new char[buffer.size()];
                        memcpy(c_buffer, buffer.c_str(), buffer.size());
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

                            const std::vector<_utils::_debug::Frame>* frames = this->stacktrace->getFrames();
                            for(unsigned int i = 0; i < frames->size(); i++){
                                _utils::_debug::Frame frame = frames->at(i);
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

    /**
     * @brief Stringify the arg
     * 
     * @param arg anything you want
     */
    #define STRINGIFY(arg) #arg

#endif