/**
 * @file 
 * 
 * This is intendeed to be such as an annotation in order to mark a functional interface.
 * 
 * Whenever you approach with a functional interface, you can pass directly a lambda expression which
 * will be moved as rvalue-reference via std::move().
 * The lambda will be stored as an std::function and test(...) method will be called to perform it
 * 
 * @author Gabriele-P03
 */

#ifndef FUNCTIONAL_INTERFACE_JPL
#define FUNCTIONAL_INTERFACE_JPL

#include <functional>

namespace jpl{

    namespace _utils{

        namespace _functional{

            class FunctionalI{
                
                public:
                    FunctionalI(){}
            };
        }
    }
}

#endif