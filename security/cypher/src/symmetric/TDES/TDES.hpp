/**
 * This implementation of the Triple DES makes 3 instance of the DES class, each one with its relative key
 * 
 * For other information about how it does work properly, read DES documentation
 * 
 * 
 * @date 2023-02-26
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef TDES_SYMM_CYPHER_JPL
#define TDES_SYMM_CYPHER_JPL

#include "../DES/DES.hpp"

namespace jpl{

    namespace _security{

        namespace _cypher{

            namespace _symmetric{

                class TDES{

                    private:

                        //It says if the IV has been set via set_CBC_IV()
                        bool iv_initialized;
                        //It contains the IV
                        bool* IV;

                        DES *first, *second, *third;

                    public:
                        TDES(std::string key1, std::string key2, std::string key3);
                        ~TDES();

                        std::string* ecb_encrypt(std::string plain_text);
                        std::string* ecb_decrypt(std::string cyphered_text);

                        std::string* cbc_encrypt(std::string plain_text);
                        std::string* cbc_decrypt(std::string cyphered_text);

                        void set_CBC_IV(std::string IV);
                };
            }
        }
    }
}

#endif