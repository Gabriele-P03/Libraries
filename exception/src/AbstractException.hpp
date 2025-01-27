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
    namespace jpl{
        namespace _utils{
            namespace _debug{
                class Stacktrace;
                extern Stacktrace* copy_st(const Stacktrace& st);
                extern Stacktrace* getStacktrace(unsigned long skipped, unsigned long maxFrame);
                extern std::string stktrc_str(const Stacktrace* stacktrace);
            }
        }
    }
        
    #endif

    #ifdef AUTO_LOG_EXCEPTION_JPL
        #ifndef USE_STACKTRACE_W_EXCEPTION_JPL
            #error "Exception auto-logging is available only through  USE_STACKTRACE_W_EXCEPTION_JPL macro. Define it!"
        #endif
        namespace jpl{
            namespace _logger{
                extern void error(const std::string &msg);  //Defined building LoggerWrapper;
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

                    AbstractException(const std::string &type_ex, unsigned long skip) : AbstractException(type_ex, "", skip){}
                    AbstractException(const std::string &type_ex, const std::string &msg, unsigned long skip){
                        this->type_ex = type_ex;
                        this->msg = msg;
                        #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                            this->stacktrace = _utils::_debug::getStacktrace(skip, 2048);
                        #endif
                    }

                    AbstractException(const AbstractException &a){
                        this->msg = a.msg;
                        this->type_ex = type_ex;
                        #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                            this->stacktrace = _utils::_debug::copy_st(*a.stacktrace);
                        #endif
                    }

                    AbstractException& operator= (const AbstractException& a){
                        this->msg = a.msg;
                        this->type_ex = type_ex;
                        #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                            this->stacktrace = _utils::_debug::copy_st(*a.stacktrace);
                        #endif
                        return *this;
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

                            buffer += _utils::_debug::stktrc_str(this->stacktrace);

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

                    ~AbstractException(){
                        #ifdef USE_STACKTRACE_W_EXCEPTION_JPL
                            delete this->stacktrace;
                        #endif
                    }
            };
        }
    }
#endif