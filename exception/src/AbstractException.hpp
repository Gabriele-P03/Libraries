/**
 * @file
 * 
 * An AbstractException is a template used by JPL's exception to be thrown as following a certain syntax.
 * It is extended by each of those exceptions, giving to the constructor of this class its class name in order to
 * print, once thrown, an error as the below one:
 *  
 *  TYPE_EXCEPTION: msg
 * 
 * As you can see in every JPL's Exception header file, their constructor are declared as public although you should avoid to
 * call them since they supply 4 args. You should call macro "constructor" which will pass to 
 * constructor __FILENAME__, __FUNCTION__ and __LINE__ 
 * 
 * This class does not include JPL's Logger therefore it will not print the exception by itselves.
 * 
 * This class, as its children, do not call any destructor, neither they're declared, since they are thought to work with
 * string literals; therefore, if you have passed an allocated const char*, you have to take care about free it.
 * 
 * Some of the provided exception override what() function and do not offer a constructor with message parameter
 * because it is useless for it; for instance, in IndexOutOfBounds you just pass Max, Attempted and Object (this last will be talked about later)
 * 
 * Some others offer constructor which you can pass anything you want to, since it will be stringified. That parameter should be used to
 * tell what has encountered the exception due to some wrong parameter passed; for instance, IndexOutOfBounds' Object field  or even
 * StackOF and UF 
 * 
 * @date 2023-04-16
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ABSTRACT_EXCEPTION_JPL
#define ABSTRACT_EXCEPTION_JPL

#include <iostream>

#include <string.h> //For strrchr()

/*
    Since __FILE__ returns the absolute path of the file where the function thrower is called, these ones are
    used to remove path that comes before filename
*/
#ifdef __linux__
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#elif defined(__WIN32)
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

namespace jpl{

    namespace _exception{

        class AbstractException : protected std::exception{

            protected:
                
                /**
                 * This is a description of the exception which has been thrown. It is passed by constructor
                 * and it is as the exception name
                 * 
                 */
                const char* type_ex;

                /**
                 * It is a description of what has just happened. For some exception it may be a template
                 * of stuff (usually when constructor does not need any msg)
                 */
                const char* msg;

                /** 
                 * File which contains the call to function_name. Get by __FILENAME__ preprocessor
                 */
                const char* file_name; 
                /**
                 * Name of the function which has caused the exception. Get by __func__ preprocessor   
                 */         
                const char* function_name; 
                /**
                 * Line where exception is thrown. Get by __LINE__ preprocessor
                 */          
                const int line;            
                
                AbstractException(const char* type_ex, const char* msg, const char* file_name, const char* function_name, const int line) : 
                    type_ex(type_ex), msg(msg), file_name(file_name), function_name(function_name), line(line){

                }

                AbstractException(const char* type_ex, const char* file_name, const char* function_name, const int line) : 
                    AbstractException(type_ex, "", file_name, function_name, line){}
            
            public:
                
                
                inline virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
                    std::string buffer = 
                        std::string(this->type_ex) + " thrown by " + std::string(this->function_name) + 
                                                     " at line "   + std::to_string(this->line) + 
                                                     " of "        + std::string(this->file_name) +  
                                                     ": "         + std::string(this->msg) + "\n";


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