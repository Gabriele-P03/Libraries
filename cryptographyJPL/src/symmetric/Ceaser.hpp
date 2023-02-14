/**
 * The Ceaser Cypher is a symmetric substitution cypher with a single integer key used as a shift right counter.
 * Every letters of the alphabet are right-shifted as the key said.
 * 
 * 
 * Once instanced this class, the key cannot be retrieved
 * 
 * 
 * @date 2023-02-11
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ATBASH_SYMM_CHYPER_JPL
#define ATBASH_SYMM_CHYPER_JPL

#include <jpl/logger/PrintLogger.hpp>
#include "../CypherConst.hpp"
#include "../CypherError.hpp"
#include <string>

namespace jpl{

    namespace _cypher{

        namespace _symmetric{

            class Ceaser{

                private:
                    unsigned int key;
                
                public:

                    /**
                     * Construct a new Ceaser Cypher object.
                     *
                     * @param key 
                     */
                    Ceaser(unsigned int key){

                        if(key > MAX_DEC_CHAR_CYPHER_JPL){
                            jpl::print("Ceaser Cypher Error Occurred");
                            jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_KEY_ERROR;
                        }

                        this->key = key;
                    }

                    /**
                     * Encrypt the given clear-text using the Ceaser Cypher and the key passed to the constructor
                     * 
                     * @param clearText 
                     * @param clearTextSize 
                     * @param buffer 
                     * @param bufferSize 
                     * @return 0 success or -1
                     */
                    inline int encrypt(const char* clearText, std::size_t clearTextSize, char* &buffer, std::size_t &bufferSize){
                        jpl::_cypher::checkExceptionAfterCall();

                        bufferSize = clearTextSize;
                        buffer = new char[bufferSize];

                        for(std::size_t i = 0; i < clearTextSize; i++){
                            char current = clearText[i];
                            unsigned int dec = (unsigned int)current;

                        }

                        return 0;
                    }


                    /**
                     * Decrypt the given crypted text using the Ceaser Cypher and the key passed to the constructor 
                     * 
                     * @param cryptedText 
                     * @param cryptedTextSize 
                     * @param buffer 
                     * @param bufferSize 
                     * @return 0 success or -1 
                     */
                    inline int decrypt(const char* cryptedText, std::size_t cryptedTextSize, char* &buffer, std::size_t &bufferSize);

            };
        }
    }
}

#endif