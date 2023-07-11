/**
 * @file 
 * 
 * A bi-predicate is a boolean-function which can be passed as a functional interface.
 * Being a boolean-function, it can be evaluated by a lambda expression which accepts two any type of 
 * parameters and returns a boolean value 
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef BI_PREDICATE_FUNCTIONAL_INTERFACE_JPL
#define BI_PREDICATE_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T, typename E>
            class BiPredicate : public FunctionalI{

                protected:

                    /**
                     * @brief The bi-predicate function
                     * 
                     * @param T first input type
                     * @param E second input type
                     */
                    std::function<bool(T, E)> predicate;

                public:

                    template<typename PredType>
                    BiPredicate(PredType predicate) : predicate{ std::move(predicate)}
                    {

                    }

                    /**
                     * @brief Evaluate the bi-predicate
                     * 
                     * @param t first input
                     * @param e second input
                     * @return result
                     */
                    inline bool test(T t, E e){
                        return this->predicate(t, e);
                    }
            };
        }
    }
}

#endif