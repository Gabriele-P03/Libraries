/**
 * It does provide useful function to operate between vectors
 * 
 * @date 2023-03-25
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef VECTORSUTILS_JPL
#define VECTORSUTILS_JPL

namespace jpl{

    namespace _utils{

        namespace _vector{

            inline int* addVV( int* v1, int* v2, unsigned int _size ){
                int* buffer = new int[_size];
                for(unsigned int i = 0; i < _size; i++)
                    buffer[i] = v1[i] + v2[2];
                return buffer;
            }
        }
    }
}

#endif