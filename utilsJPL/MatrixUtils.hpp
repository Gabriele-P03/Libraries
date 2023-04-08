/**
 * Here it does provide you some useful functions to operate wth matrix-matrix and matrix-vector.
 * 
 * 
 * @date 2023-03-25
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef MATRIXUTILS_JPL
#define MATRIXUTILS_JPL

namespace jpl{

    namespace _utils{


        /**
         * It does provide the multiplication row for col between two matrix.
         * Since two pointers are needed, you can even call this function to multriplicate matrix-vector
         * 
         * @param row 
         * @param col 
         * @param _size of row and col
         * @return result of multiplication
         */
        inline int mulRC(int* row, int* col, unsigned int _size){

            int buffer = 0;
            for(unsigned int i = 0; i < _size; i++){
                buffer += row[i] * col[i];
            }
            return buffer;
        }

        /**
         * It does provide the multiplication between a matrix and a vector
         * 
         * @param mat 
         * @param v 
         * @param size 
         * @return int* 
         */
        inline int* mulMV(int** mat, int* v, unsigned int size){

            int* buffer = new int[size];
            for(unsigned int i = 0; i < size; i++){

                buffer[i] = mulRC(mat[i], v, size);
            } 
            return buffer;
        }
    }
}

#endif