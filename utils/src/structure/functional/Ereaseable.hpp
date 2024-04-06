/**
 * This is a wrapper header file which is used whenever a deletion of an element is needed.
 * If the typename is a pointer, the real deletion is performed only when DEL_EFF_DS_JPL macro is defined before 
 * have included the collection's header file 
 * 
 * @date 10/09/2023
 * @author Gabriele-P03
*/

#ifndef EREASEABLE_JPL
#define EREASEABLE_JPL

#include <assert.h>

namespace jpl{

    namespace _utils{

        template <typename T>
        class Ereaseable{

            public:
                static void erease(T &value){}
                static void v_erease(T* &list, unsigned long size){
                }
        };

        template <typename P>
        class Ereaseable<P *>{

            public:
                static void erease(P* &value){
                    delete value;
                    value = nullptr;
                }
                static void v_erease(P** &list, unsigned long size){
                    for(unsigned long i = 0; i < size; i++){
                        delete list[i];
                    }
                }
        };
    }
}

#endif