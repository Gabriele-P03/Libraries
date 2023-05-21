/**
 * @file
 * 
 * There are some functions about bit-operation.
 * Since there's no bit-type in C++, it is associated as a boolean value (true value means 1 otherwise 0)
 *  
 * Into ConversionUtils.hpp you can figure out some function which could help you to convert 
 * chars to bits (boolean array)
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

            /**
             * Performs xor operation between two array of bits 
             * 
             * @param _src1 first array
             * @param _src2 second array
             * @param _size size of _src1 and _src2
             * @return xored array
             */
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