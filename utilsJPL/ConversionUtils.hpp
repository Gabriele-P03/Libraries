/**
 * Some functions useful whenever you have to convert a type into another one (only standard type definition are contempled).
 * 
 * Here you are convertions available:
 * 
 *  - Integer to Const Char*
 *  - Const Char* to Integer
 * 
 *  - Unsigned Int to Const Char*
 *  - Const Char* to Unsigned Int
 * 
 *  - Float to Const Char*
 *  - Const Char* to Float
 * 
 *  - Double to Const Char*
 *  - Const Char* to Double
 *  
 *  - Bool to Const Char* (with offset, to store 8 bools into a value)
 *  - Const Char* to Bool (with offset, to store 8 bools into a value)
 * 
 * @date 2023-02-04
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef CONVERTION_UTILS_JPL
#define CONVERTION_UTILS_JPL

#include <string.h>

namespace jpl{
	
	namespace _utils{

		inline void int_cc(int src, const char* &dst){
		    memcpy((void*)&dst[0], &src, 4);
		}
		inline void cc_int(const char* src, int &dst){
		    memcpy(&dst, src, 4);
		}


		inline void uint_cc(unsigned int src, const char* &dst){
		    memcpy((void*)&dst[0], &src, 4);
		}
		inline void cc_uint(const char* src, unsigned int &dst){
		    memcpy(&dst, src, 4);
		}


		inline void f_cc(float src, const char* &dst){
		    memcpy((void*)&dst[0], &src, 4);
		}
		inline void cc_f(const char* src, float &dst){
		    memcpy(&dst, src, 4);
		}


		inline void d_cc(double src, const char* &dst){
		    memcpy((void*)&dst[0], &src, 4);
		}
		inline void cc_d(const char* src, double &dst){
		    memcpy(&dst, src, 4);
		}

		inline void b_cc(bool src, const char* &dst, unsigned short offset){
		    ((dst[0] << offset) | src);
		}
		inline void cc_b(const char* src, bool &dst, unsigned short offset){
		    dst = (( (src[0] >> offset) << sizeof(char) - 1 - offset));
		}

	}
}

#endif
