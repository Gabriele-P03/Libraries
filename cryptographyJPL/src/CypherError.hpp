#ifndef CYPHER_STATUS_CODE_JPL
#define CYPHER_STATUS_CODE_JPL

#include <functional>
#include <jpl/utils/CharUtils.hpp>
#include <jpl/logger/PrintLogger.hpp>

namespace jpl{

    namespace _cypher{

        typedef unsigned short ERROR;

        /**
         * If any function of this framework return -1, then you should get this value in order to
         * get know about the error occurred during its work.
         * 
         */
        extern ERROR _error_cypher_jpl;

        /**
         * It checks if an ecryption/decryption function is called altough an error has been occurred.
         * You oughta opt to check _error_cypher_jpl similar to CYPHER_JPL_NO_ERROR before any function call,
         * since this one will throw an exception
         */
        inline void checkExceptionAfterCall(){
            jpl::print("Checking for any excetion before to encrypt/decrypt...");
            if(_error_cypher_jpl){
                jpl::print("There's an error in queue...", jpl::logger::ERR);
                throw new std::bad_function_call();
            }
            jpl::print("No errors in queue...");
        }
    }
}

#define CYPHER_JPL_NO_ERROR  0
#define CYPHER_JPL_KEY_ERROR  1
#define CYPHER_JPL_CLEARTEXT_SYNTAX_ERROR  2

#endif