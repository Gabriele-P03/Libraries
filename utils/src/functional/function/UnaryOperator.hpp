/**
 * @file 
 * 
 * An UnaryOperator is a Function whose return-type is equal (as a duty) to the type of the given parameter
 * to the function
 * 
 * @date 2023-05-28
 * @author Gabriele-P03
 */

#ifndef UNARY_OPERATOR_FUNCTIONAL_INTERFACE_JPL
#define UNARY_OPERATOR_FUNCTIONAL_INTERFACE_JPL

#include "Function.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T>
            class UnaryOperator : public Function<T, T>{

                public:

                    template<typename FunctionType>
                    UnaryOperator(FunctionType function) : Function<T, T>(function)
                    {

                    }

            };
        }
    }
}

#endif