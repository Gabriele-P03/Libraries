/**
 * The AtBash is one of the most unsafe symmetric crypthography algorithm. It is a substitution cypher wich does not 
 * require any key to work. It hust substitute A with Z, B with Y and so on.
 * The first appearing of this cypher is done in the Holy Bible.
 * 
 * Since its unreliability, it is very unsuggested to use it; but if you're working either on school homework o game developing,
 * or any other kind of project wich does not need a stronger chypher, this is fit for your goal: quick computation. 
 * 
 * Since the AtBash is a no-key cypher, it has not been developed with a point of view OOP.
 * 
 * Since the AtBash is a substitution cypher, special characters will not be manipulate during the crypting.
 * 
 * First the function makes sure that the char it will manipulate is a valid one (i.e. it is a letter), then
 * it makes ensure that it is a lower one, manipulated with the Atbash algorithm and, if it was an upper one, it is transformed
 * as upper.
 * 
 * The single function provided by this header file can be used to encrypt and decrypt both.
 * 
 * @date 2023-02-11
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ATBASH_SYMM_CHYPER_JPL
#define ATBASH_SYMM_CHYPER_JPL

#include <string>
#include <jpl/utils/CharUtils.hpp>
#include "../CypherConst.hpp"

namespace jpl{

    namespace _security{

        namespace _cypher{

            namespace _symmetric{
                
                inline int atbash(std::string cleartext, std::string &_out){
                    
                    std::string buffer = "";
                    for(std::size_t i = 0; i < cleartext.size(); i++){

                        //Check if the char is a valid letter
                        char tmp = cleartext.at(i);
                        if(_utils::isLetter(tmp)){
                            unsigned int dec = (unsigned int)tmp;
                            unsigned int x = (_utils::isLowercaseLetter(tmp) ? 
                                SYM_0_JPL + SYM_1_JPL :
                                SYM_2_JPL + SYM_3_JPL    
                            );
                            x -= dec;
                            tmp = (char)x;
                        }
                        buffer.push_back(tmp);
                    }
                    return 0;
                }
            }
        }
    }
}

#endif