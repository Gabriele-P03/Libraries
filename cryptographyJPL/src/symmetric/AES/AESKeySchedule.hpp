/**
 * This header file contains definitions of functions used by the AES key schedule and declaration of matrices and vectors used
 * by them (their definition can be seen into relative source file).
 * 
 * 
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef AES_SYMM_KEY_SCHEDULE_JPL
#define AES_SYMM_KEY_SCHEDULE_JPL

#include <jpl/utils/ConversionUtils.hpp>

namespace jpl{

    namespace _cypher{

        namespace _symmetric{

            namespace _aes_key_schedule{

                /*
                *
                *   ROTATE
                *
                */

                /**
                 * Execute the rotation transformation on the given buffer.
                 * Rotated buffer is stored into itselves
                 * @param buffer 
                 */
                static inline void rotate(char* &buffer){
                    const char tmp = buffer[0];
                    buffer[0] = buffer[1];
                    buffer[1] = buffer[2];
                    buffer[2] = buffer[3];
                    buffer[3] = tmp; 
                }



                /**
                 *  
                 *  SUB-WORDS
                 * 
                 */

                extern const unsigned char mul_inv[16][16];

                /**
                 * Id gets the b number, it means the multiplicative inverse of c
                 * 
                 * @param c 
                 * @return int 
                 */
                static inline unsigned char multiplicative_inverse(unsigned char c){
                    int* splitted = _utils::split_cc_ii(c);
                    unsigned char b = mul_inv[splitted[0]][splitted[1]];
                    delete[] splitted;
                    return b;
                }

                /**
                 * It executes the affine transformation
                 * 
                 * @param c 
                 * @return int 
                 */
                static inline unsigned char affine_transformation(unsigned char c){
                    
                    unsigned char b = multiplicative_inverse(c);
                    return (
                        b ^
                        (b << 1) ^
                        (b << 2) ^
                        (b << 3) ^
                        (b << 4) ^
                        0x63
                    );
                }

                static inline unsigned char* sub_word(unsigned char words[4]){
                    return new unsigned char[4]{
                        affine_transformation(words[0]), affine_transformation(words[1]), affine_transformation(words[2]), affine_transformation(words[3])
                    };
                }



                /*
                 *
                 *  ROUND-CONSTANTS
                 *  
                 * FINISCI DI SCRIVERE GLI RCON 
                 */

                extern const unsigned char rcon[14];
            }
        }
    }
}

#endif