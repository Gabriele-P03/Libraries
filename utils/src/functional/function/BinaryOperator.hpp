/**
 * @file 
 * 
 * An BinaryOperator is a Function whose return-type is equal (as a duty) to the type of the given two 
 * parameters to the function
 * 
 * @date 2023-05-28
 * @author Gabriele-P03
 */

#ifndef BINARY_OPERATOR_FUNCTIONAL_INTERFACE_JPL
#define BINARY_OPERATOR_FUNCTIONAL_INTERFACE_JPL

#include "BiFunction.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T>
            class BinaryOperator : public BiFunction<T, T, T>{

                public:

                    template<typename FunctionType>
                    BinaryOperator(FunctionType function) : BiFunction<T, T, T>(function)
                    {

                    }

            };
        }
    }
}

#endif