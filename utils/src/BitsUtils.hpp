/**
 * This header file contains some functions spread off the whole jpl framework, they do operation at lower-level on bits.
 * Since a bit cannot be explictly represented, it is done by a boolean value 
 * 
 * @date 2023-04-16
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef BITS_UTILS_JPL
#define BITS_UTILS_JPL

namespace jpl{

    namespace _utils{

        namespace _bits{

            inline bool* _xor_bits(bool* _src1, bool* _src2, unsigned long _size){
                bool* _buffer = new bool[_size];

                for(unsigned long i = 0; i < _size; i++){
                    _buffer[i] = (_src1[i] != _src2[i]);
                }

                return _buffer;
            }
        }
    }
}



#endif