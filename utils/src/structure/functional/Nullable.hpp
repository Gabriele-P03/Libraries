/**
 * This is a wrapper header file which is used whenever a collection needs to either check if an element is null or, in case
 * of pointer element, to assign nullptr value
 * 
 * 
 * @date 10/09/2023
 * @author Gabriele-P03
*/

#ifndef NULLABLE_JPL
#define NULLABLE_JPL

namespace jpl{

    namespace _utils{

        template <typename T>
        class Nullable{

            public:
                static bool isNull(T &value){return false;}
                static void nullify(T* &value){}
        };

        template <typename P>
        class Nullable<P *>{

            public:
                static bool isNull(P* &value){return value == nullptr;}
                static void nullify(P* &value){value = nullptr;}
        };
    }
}

#endif