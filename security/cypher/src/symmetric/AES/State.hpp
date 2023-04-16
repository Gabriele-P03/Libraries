/**
 * A State is the matrix of bytes which AES cypher works on.
 * 
 * It is made up by 4 rows and x columns;
 * x is the result of the division of the size bytes given in input to AES by 32.
 * Since AES is developed to work with 128, 192 and 256 bits, there are 3 columns size already available for a state matrix 
 * 
 * @date 2023-03-19
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */
#ifndef AES_SYMM_STATE_JPL
#define AES_SYMM_STATE_JPL

#include "AESType.hpp"
#include "../../CypherError.hpp"

namespace jpl{

    namespace _security{

        namespace _cypher{

            namespace _symmetric{

                class State{

                    private:
                        const AES_TYPE* aes_type;

                        unsigned short cols;

                        const char** state;

                    public:

                        State(const AES_TYPE* aes_type);

                        /**
                         * Once it has set the aes_type field, this function build up the state matrix as 
                         * it is required by aes_type
                         * 
                         */
                        void instanceState();

                        /**
                         * @return how many columns are into the state
                         */
                        inline unsigned short getCols(){
                            return this->cols;
                        }

                        ~State();

                };
            }
        }
    }
}

#endif