/**
 * The Ceaser Cypher is a symmetric substitution cypher with a single integer key used as a shifter.
 * 
 * This version of Ceaser Cypher provides:
 * 
 *      1. ASCII encoder/decoder which use all 128 chars available of the ASCII table; define _USE_ASCII_CYPHER_JPL
 *      2. Alphabet encoder/decoder which use all letters of the alphabet (uppercase and lower one); define _USE_ALPHABET_CYPHER_JPL
 *      3. Numbers encoder/decoder which use all 10 digits 0-9; define _USE_NUMBERS_CYPHER_JPL
 * 
 * 
 * The priority is given to ASCII macro; it means that if you define all those three macro, the only one checked is the ASCII one. 
 * 
 * 
 * NUMBERS and ALPHABET charset can be defined together. 
 * The not defining of one of them will prevent the crypting of relative chars.
 * 
 * Any lowercase letters are crypted with another lower one, altough ALPHABET macro will use uppercase ones.
 * e.g.     
 *  xyz -> key=1 -> yza (not yzA, despite in ascii table uppercase letters come before lower ones)
 * Idem for uppercase letters.
 * 
 * Any chars which are not set to be crypted will be left as the were
 * 
 * Due to security reason, the key cannot be retrieved via any getter once the object is instanced
 * 
 * Altough it does print you a warning about any errors occurred, you oughta always check for any error
 * stored into _error_cypher_jpl
 * 
 * @date 2023-02-11
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef CEASER_SYMM_CHYPER_JPL
#define CEASER_SYMM_CHYPER_JPL

#include <jpl/logger/PrintLogger.hpp>
#include "../CypherConst.hpp"
#include "../CypherError.hpp"
#include <jpl/utils/CharUtils.hpp>
#include <string>

#ifdef _USE_ASCII_CYPHER_JPL
    #define MAX_KEY_CYPHER_JPL 128  //ASCII contains 128 chars
#elif defined(_USE_ALPHABET_CYPHER_JPL) || defined(_USE_NUMBERS_CYPHER_JPL)

    #if defined(_USE_ALPHABET_CYPHER_JPL) && !defined(_USE_NUMBERS_CYPHER_JPL)
        #define MAX_KEY_CYPHER_JPL 52   //Uppercase letters + lowercase ones

    #elif !defined(_USE_ALPHABET_CYPHER_JPL) && defined(_USE_NUMBERS_CYPHER_JPL)
        #define MAX_KEY_CYPHER_JPL 10   //Digits

    #else
        #define MAX_KEY_CYPHER_JPL 62//Uppercase letters + lowercase ones + digits
    
    #endif
#else
    #error "No Charset Selected"
#endif

namespace jpl{

    namespace _security{

        namespace _cypher{

            namespace _symmetric{

                class Ceaser{

                    private:
                        unsigned int key;

                        #if (defined(_USE_ALPHABET_CYPHER_JPL) || defined(_USE_NUMBERS_CYPHER_JPL)) && !defined(_USE_ASCII_CYPHER_JPL) 

                            inline char getCryptedChar(unsigned int _start){
                                unsigned int _value;
                                if(jpl::_utils::isLowercaseLetter((char)_start)){
                                    _value = SYM_0_JPL + ((this->key - SYM_0_JPL + _start) % 26);
                                }else if(jpl::_utils::isUppercaseLetter((char)_start)){
                                _value = SYM_2_JPL + ((this->key - SYM_2_JPL + _start) % 26);
                                }else if(jpl::_utils::isNumber( (char)_start )){
                                    _value = SYM_8_JPL + ((this->key - SYM_0_JPL + _start) % 10);
                                }

                                return (char)_value;
                            }

                            inline char getClearChar(unsigned int _end){
                                unsigned int _value;
                                if(jpl::_utils::isLowercaseLetter((char)_end)){
                                    _value = SYM_1_JPL - ((SYM_1_JPL - _end + this->key) % 26);
                                }else if(jpl::_utils::isUppercaseLetter((char)_end)){
                                    _value = SYM_3_JPL - ((SYM_3_JPL - _end + this->key) % 26);
                                }else if(jpl::_utils::isNumber( (char)_end )){
                                    _value = SYM_9_JPL - ((SYM_9_JPL - _end + this->key) % 10);
                                }

                                return (char)_value;
                            }

                        #endif


                    
                    public:

                        /**
                         * Construct a new Ceaser Cypher object with the given symmetric key.
                         * You oughta check _error_cypher_jpl for any errors occurred.
                         * 
                         * @param key 
                         */
                        Ceaser(unsigned int key){
                            if(key >= MAX_KEY_CYPHER_JPL){
                                jpl::_security::_cypher::_error_cypher_jpl = CYPHER_JPL_KEY_SIZE_ERROR;
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
                            if( !jpl::_security::_cypher::checkError()){
                                return -1;
                            }

                            bufferSize = clearTextSize;
                            buffer = new char[bufferSize];

                            for(std::size_t i = 0; i < clearTextSize; i++){

                                char current = clearText[i];

                                #ifdef _USE_ASCII_CYPHER_JPL
                                    unsigned int dec = (unsigned int)current;
                                    dec += this->key;
                                    if(dec >= MAX_KEY_CYPHER_JPL)
                                            dec -= MAX_KEY_CYPHER_JPL;
                                    buffer[i] = (char)dec;
                                #elif defined(_USE_ALPHABET_CYPHER_JPL) || defined(_USE_NUMBERS_CYPHER_JPL)

                                    #ifndef _USE_ALPHABET_CYPHER_JPL
                                        if(jpl::_utils::isLetter(current)){
                                            buffer[i] = current;
                                            continue;
                                        }
                                    #endif

                                    #ifndef _USE_NUMBERS_CYPHER_JPL 
                                        if(jpl::_utils::isNumber(current)){
                                            buffer[i] = current;
                                            continue;
                                        }
                                    #endif

                                    char tmp = this->getCryptedChar(current);
                                    buffer[i] = tmp;
                                #endif

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
                        inline int decrypt(const char* cryptedText, std::size_t cryptedTextSize, char* &buffer, std::size_t &bufferSize){

                            bufferSize = cryptedTextSize;
                            buffer = new char[bufferSize];

                            for(std::size_t i = 0; i < cryptedTextSize; i++){

                                char current = cryptedText[i];

                                #ifdef _USE_ASCII_CYPHER_JPL
                                    int dec = (unsigned int)current;
                                    dec -= this->key;
                                    if(dec < 0)
                                            dec += MAX_KEY_CYPHER_JPL;
                                    buffer[i] = (char)dec;                            
                                #elif defined(_USE_ALPHABET_CYPHER_JPL) || defined(_USE_NUMBERS_CYPHER_JPL)

                                    #ifndef _USE_ALPHABET_CYPHER_JPL
                                        if(jpl::_utils::isLetter(current)){
                                            buffer[i] = current;
                                            continue;
                                        }

                                    #endif

                                    #ifndef _USE_NUMBERS_CYPHER_JPL 
                                        if(jpl::_utils::isNumber(current)){
                                            buffer[i] = current;
                                            continue;
                                        }
                                    #endif

                                    char tmp = this->getClearChar(current);
                                    buffer[i] = tmp;

                                #endif
                            }

                            return 0;
                        }

                };
            }
        }
    }
}

#endif