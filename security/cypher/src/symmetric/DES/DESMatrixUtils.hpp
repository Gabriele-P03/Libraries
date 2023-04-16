/**
 * Here there are all matrices - with their relative cols and rows size - used by DES cypher 
 * 
 * @date 2023-04-16
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef DES_CYPHER_MATRIX_UTILS_JPL
#define DES_CYPHER_MATRIX_UTILS_JPL

namespace jpl{

    namespace _security{

        namespace _cypher{

            namespace _symmetric{

                namespace _des{

                    extern const unsigned short pc1_matrix_size;
                    extern const unsigned short *pc1_matrix;

                    extern const unsigned short pc2_matrix_size;
                    extern const unsigned short *pc2_matrix;

                    extern const unsigned short ip_matrix_size;
                    extern const unsigned short *ip_matrix;

                    extern const unsigned short exp_matrix_size;
                    extern const unsigned short *exp_matrix;

                    extern const unsigned short s_boxes_size;
                    extern const unsigned short s_box_size;
                    extern const unsigned short **s_boxes;

                    extern const unsigned short p_matrix_size;
                    extern const unsigned short *p_matrix;

                    extern const unsigned short fp_matrix_size;
                    extern const unsigned short *fp_matrix;
                }
            }
        }
    }
}

#endif
