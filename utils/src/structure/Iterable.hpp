/**
 * @file
 * 
 * This is a functional interface which marks class which extends this one as
 * they can be involved in a forEach loop with an instance of JPL's consumer
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

                /**
                 * @brief Iterate all elements of the collection and execute consumer 
                 * on each element <br>
                 * Unless you have checked if T is nullptr - if it is a pointer - segmentation-fault may occurr
                */
                virtual void forEach(_functional::Consumer<T> consumer) = 0;
        };
    }
} 


#endif