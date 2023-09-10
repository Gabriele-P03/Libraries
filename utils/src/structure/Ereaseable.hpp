/**
 * This is a wrapper header file which helps a collection to delete its element in a best-effort way.
 * 
 * How it delete the element, unless it is not a pointer, is via an implementation of helper class which
 * checks type of T - if it is a pointer or not - and then use the relative erease() method
 * 
 * @date 10/09/2023
 * @author Gabriele-P03
*/

#ifndef EREASEABLE_JPL
#define EREASEABLE_JPL

namespace jpl{

    namespace _utils{

        template <typename T>
        class Ereaseable{

            public:
                static void erease(T &value){}
        };

        template <typename P>
        class Ereaseable<P *>{

            public:
                static void erease(P *value){
                    delete value;
                }
        };
    }
}

#endif