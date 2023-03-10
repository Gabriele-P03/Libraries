/**
 * This is the implementation of AES chypher.
 * It works with 128-192-265 bits key.
 * 
 * 
 * @date 2023-03-04
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef AES_SYMM_CYPHER_JPL
#define AES_SYMM_CYPHER_JPL

#include <string>
#include "../../CypherError.hpp"

namespace jpl{

    namespace _cypher{

        namespace _symmetric{

            //Struct which describe as index-key_length_bits the AES types (128, 192, 256)
            typedef struct AES_TYPE{

                unsigned short index;
                unsigned short key_length_bits;
                AES_TYPE(unsigned short index, unsigned short key_length_bits);
            };

            class AES{

                private:

                    //The AES Type selected
                    const AES_TYPE* aes_type;
                    //Raw key
                    std::string raw_key;

                    void checkKey(std::string raw_key);

                public:

                    static const AES_TYPE aes_128, aes_192, aes_256;  

                    AES(std::string raw_key, const AES_TYPE* aes_type);
                    ~AES();

                    AES_TYPE getAESType();
            };
        }
    }
}

#endif