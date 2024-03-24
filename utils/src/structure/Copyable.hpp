/**
 * This is a wrapper header file which helps a collection to copy its elements in a best-effort way.
 * 
 * 
 * @date 10/09/2023
 * @author Gabriele-P03
*/

#ifndef COPYABLE_JPL
#define COPYABLE_JPL

#include <string.h>

namespace jpl{

    namespace _utils{

        template <typename T>
        class Copyable{

            public:
                static void copy(T& dst, const T src){
                    memcpy(&dst, &src, sizeof(src));
                }
        };

        template <typename P>
        class Copyable<P *>{

            public:
                static void copy(P* &dst, const P* src){
                    if(dst == nullptr)
                        dst = (P*)malloc(sizeof(src));
                    memcpy(dst, src, sizeof(src));
                }
        };
    }
}

#endif