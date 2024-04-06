/**
 *  This is a wrapper header file which is used whenever a collection needs to get know if T is a pointer
 * 
 * 
 * @date 10/09/2023
 * @author Gabriele-P03
*/

#ifndef POINTERABLE_JPL
#define POINTERABLE_JPL

namespace jpl{

    namespace _utils{

        template <typename T>
        class Pointerable{

            public:
                static bool isPointer(){return false;}
        };

        template <typename P>
        class Pointerable<P *>{

            public:
                static bool isPointer(){return true;}
        };
    }
}

#endif