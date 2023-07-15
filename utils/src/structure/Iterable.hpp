/**
 * @file
 * 
 * This is an interface
 * 
 * Every class which extends this one is marked as it can be involved into a for-each loop
 * 
 * @date 2023-07-12
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
*/

#ifndef ITERABLEI_JPL
#define ITERABLEI_JPL

#include "../functional/consumer/Consumer.hpp"

namespace jpl{
    
    namespace _utils{

        template<typename T>
        class Iterable{

            public:

                virtual void forEach(_functional::Consumer<T*> consumer) = 0;
        };
    }
} 


#endif