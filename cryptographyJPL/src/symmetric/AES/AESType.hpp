/**
 * AES Type describes the length of the input given to AES cypher
 * 
 * @date 2023-03-20
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef AES_SYMM_TYPE_JPL
#define AES_SYMM_TYPE_JPL

namespace jpl{

    namespace _cypher{

        namespace _symmetric{

            class AES_TYPE{

                private:
                    const unsigned short index;
                    const unsigned short bits_length;
                    const unsigned short rounds;

                    AES_TYPE(const unsigned short index, const unsigned short bits_length, const unsigned short rounds);
                
                public:

                    static const AES_TYPE *AES128, *AES192, *AES256;

                    constexpr unsigned short getIndex() const {
                        return this->index;
                    }
                    constexpr unsigned short getLength() const {
                        return this->bits_length;
                    }
                    constexpr unsigned short getRounds() const{
                        return this->rounds;
                    }
            };
        }
    }
}

#endif