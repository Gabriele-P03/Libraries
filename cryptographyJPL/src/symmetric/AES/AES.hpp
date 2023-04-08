/**
 * This is the implementation of AES chypher.
 * It works for each three types of keys (128, 192 and 256)
 * 
 * I guess to remember you that AES matrix works in a column major arrangement.
 * 
 *  * Here there are:
 *  - SubBytes
 *  - ShiftRows
 *  - MixColumns
 *  - AddRoundKey
 * 
 * The last round does not have the mix columns function.
 * The subBytes does the substitution whilst shiftRows and MixColumns performs the permutation
 * 
 * @date 2023-03-04
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef AES_SYMM_CYPHER_JPL
#define AES_SYMM_CYPHER_JPL

#include "State.hpp"
#include <string>
#include "../../CypherError.hpp"

namespace jpl{

    namespace _cypher{

        namespace _symmetric{

            class AES{

                private:

                    //The AES Type selected
                    const AES_TYPE* aes_type;
                    //Raw key
                    std::string* raw_key;

                    void checkKey(std::string* raw_key);

                public:

                    AES(std::string* raw_key, const AES_TYPE* aes_type);
                    ~AES();

                    AES_TYPE getAESType();
            };
        }
    }
}

#endif