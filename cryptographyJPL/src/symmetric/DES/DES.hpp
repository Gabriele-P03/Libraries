/**
 * This implementation of DES provides CBC and ECB mode which can be used calling relative encryption/decryption function.
 * 
 * Do not pass either IV or key as hexdecimal, since the convertion in binary is done by the function and then
 * all ASCII chars can be used with this framework.
 * 
 * A nullptr is returned by those function whenever an error is previously occurred or during the called one.
 * You can check the last error calling jpl::_cypher::checkExceptionAfterCall().
 * 
 * Due to what has been said above, you must call set_CBC_IV() before any call to CBC mode or a nullptr will be returned.
 * 
 * The conversion from chars to binary digits has been structured using boolean array as long as eight times the const char array.
 * This conversion is performed by the external "ConversionUtils.hpp" jpl-utils header file.
 * 
 * The XOR is performed by the external "BitsUtils.hpp" jpl-utils header file.
 * 
 * All the matrices used by DES algorithm are declared inside an external header file and then defined in a source file  
 * 
 * @date 2023-02-17
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef DES_SYMM_CYPHER_JPL
#define DES_SYMM_CYPHER_JPL

/*
    The macro defined below are calculated in bits...
*/
#define DES_JPL_RAW_KEY_SIZE 64
#define DES_JPL_PC1_KEY_SIZE 56 
#define DES_JPL_PC2_KEY_SIZE 48

#define DES_JPL_ROUND 16

#include <string.h> //For memcpy(), used in _pc2()

#include "../../CypherError.hpp"
#include "DESMatrixUtils.hpp"
#include <jpl/utils/ConversionUtils.hpp>
#include <jpl/utils/BitsUtils.hpp>

namespace jpl{

    namespace _cypher{

        namespace _symmetric{

            class DES{

                private:

                    //It is not needed to define its size since DES clear key size is 64 bits...
                    //It means that this const char* is 8 bytes long
                    const char* raw_key;
                    
                    //It says if the IV has been set via set_CBC_IV()
                    bool iv_initialized;
                    //It contains the IV
                    bool* IV;
                
                    std::vector<bool*>sub_keys_bits;


                    /**
                     * Permuted Choice 1. IT CALLS _pc2, too
                     * 
                     * @return 0 for success, otherwise -1 
                     */
                    int _pc1();

                    /**
                     * It left-shifts the bits of _l and _r
                     * As DES theory tells, the amount of bits shifted is 1 for the rounds 1, 2, 9, 16; otherwise of 2 bits.
                     * 
                     * @param _l 
                     * @param _r 
                     * @param round
                     */
                    void rotate(bool* &_l, bool* &_r, unsigned short round);

                    /**
                     * Permuted Choice 2
                     * 
                     * Selecte 48 bits of key from the two sub-key (left and right).
                     * 24 bits from each of them are selected
                     * 
                     * It is called by _pc1()
                     * 
                     * @param _l 
                     * @param _r 
                     */
                    void _pc2(bool* _l, bool* _r, unsigned short round);

                    /**
                     * DES feistel function 
                     * 
                     * @param buffer 
                     * @param round 
                     * @return the binary digits after have been manipulated by feistel DES' function
                     */
                    bool* mangler(bool* buffer, unsigned short round);

                    /**
                     * Execute the DES encryption algorithm on the given sub_block
                     * 
                     * @param sub_block the current sub-block of the plain-text
                     * @return the binary digits after have been completely encrypted
                     */
                    bool* enc_sub_block(bool* sub_block);

                public:

                    DES(std::string key);
                    ~DES();

                    std::string* ecb_encrypt(std::string plain_text);
                    std::string* ecb_decrypt(std::string cyphered_text);

                    std::string* cbc_encrypt(std::string plain_text);
                    std::string* cbc_decrypt(std::string cyphered_text);

                    void set_CBC_IV(std::string IV);
            };
        }
    }
}

#endif
