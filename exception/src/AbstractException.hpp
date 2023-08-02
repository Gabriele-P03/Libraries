/**
 * @file
 * 
 * An AbstractException is a template of a basic exception used by JPL to have theirs to be thrown.
 * 
 * This class does not include JPL's Logger, therefore it will not print the exception by itselves.
 * It provides, beyond what() function, even one that returns the stacktrace as const char* and which you can
 * print - by yourself - through JPL's Logger   
 * 
 * @date 2023-04-16
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ABSTRACT_EXCEPTION_JPL
#define ABSTRACT_EXCEPTION_JPL

#include <iostream>

#define BOOST_STACKTRACE_USE_BACKTRACE
#include <boost/stacktrace.hpp>
#include <boost/exception/all.hpp>

#include <vector>

namespace jpl{

    namespace _exception{

        class AbstractException;

        typedef boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace> traced;

        template<class E, typename std::enable_if<std::is_base_of<AbstractException, E>::value>::type* = nullptr>
        void throwWithStacktrace(E &e){
            throw boost::enable_error_info(e)<<traced(boost::stacktrace::stacktrace()); 
        }

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

                AbstractException(std::string type_ex) : AbstractException(type_ex, ""){}
                AbstractException(std::string type_ex, std::string msg) : type_ex(type_ex), msg(msg){}
                
            public:
                
                /**
                 * @brief Print the type of the exception which has been thrown with the message that has been passed, too
                 * 
                 * @return const char* 
                 */
                inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + ": " + std::string(this->msg) + "\0";


                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }

                /**
                 * @return the Stacktrace of the thrown exception
                 */
                inline virtual const char* getStacktrace() const{
                    std::string buffer = std::string(this->what()) + "\n"; 

                    const boost::stacktrace::stacktrace* st = boost::get_error_info<traced>(*this);
                    std::vector<boost::stacktrace::frame> frames = st->as_vector();

                    for(unsigned long i = 0; i < frames.size(); i++){
                        boost::stacktrace::frame current = frames.at(i);
                        buffer += current.name() + " of " + current.source_file() + " at line " + std::to_string(current.source_line()) + "\n";
                    }

                    char* c_buffer = new char[buffer.size()];
                    memcpy(c_buffer, buffer.c_str(), buffer.size());
                    return c_buffer;
                }

                /**
                 * @brief 
                 * 
                 * @param os 
                 * @param iae 
                 * @return std::ostream& 
                 */
                inline friend std::ostream& operator<<(std::ostream& os, const AbstractException &iae){

                    const char* buffer = iae.what();
                    os<<buffer;
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