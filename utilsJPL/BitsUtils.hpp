#ifndef BITS_UTILS_JPL
#define BITS_UTILS_JPL

namespace jpl{

    namespace _utils{

        inline bool* _xor_bits(bool* _src1, bool* _src2, unsigned long _size){
            bool* _buffer = new bool[_size];

            for(unsigned long i = 0; i < _size; i++){
                _buffer[i] = (_src1[i] != _src2[i]);
            }

            return _buffer;
        }
    }
}



#endif