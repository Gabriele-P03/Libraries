/**
 * This is a wrapper header file which helps a collection to check nullptr element.
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
                static bool isNull(P* &value){return value == NULL;}
                static void nullify(P** &value){*value = NULL;}
        };
    }
}

#endif