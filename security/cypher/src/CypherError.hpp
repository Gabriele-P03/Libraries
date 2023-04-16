#ifndef CYPHER_STATUS_CODE_JPL
#define CYPHER_STATUS_CODE_JPL

#include <jpl/logger/PrintLogger.hpp>

namespace jpl{

    namespace _security{

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
             * This function is called as the first line code of any enc/dec functions.
             * 
             * You could check if check _error_cypher_jpl is equal to CYPHER_JPL_NO_ERROR before any enc/dec call,
             * since this one will throw an exception
             */
            inline bool checkError(){
                if(_error_cypher_jpl > 0){
                    jpl::print("An error has been found in queue: " + std::to_string(_error_cypher_jpl), jpl::_logger::ERR);
                    _error_cypher_jpl = 0;
                    return false;
                }
                return true;
            }
        }
    }
}

#define CYPHER_JPL_NO_ERROR  0
#define CYPHER_JPL_KEY_SIZE_ERROR 1
#define CYPHER_JPL_KEY_SYNTAX_ERROR 2
#define CYPHER_JPL_CLEARTEXT_SYNTAX_ERROR  3
#define CYPHER_JPL_XOR_ARGUMENT_SIZE_NOT_EQUAL 4 //
#define CYPHER_JPL_CHECK_PARITY_ERROR 5 //Error about parity bit of a byte
#define CYPHER_JPL_DES_PC1_0 6  //DES#_pc1(). Error Size. Bytes of key withouth parity bits != key.size() - 1
#define CYPHER_JPL_IV_UNINIT_ERROR 7   //IV not iniziatilzed altough a CBC mode encryption/decryption has been called
#define CYPHER_JPL_IV_SIZE_ERROR 8   //IV does not respect the size supplied by the cypher
#define CYPHER_JPL_AES_TYPE_NULLPTR 9

#endif