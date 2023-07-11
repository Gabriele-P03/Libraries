/**
 * @file 
 * 
 * A predicate is a boolean-function which can be passed as a functional interface.
 * Being a boolean-function, it can be evaluated by a lambda expression which accepts any type of 
 * parameter and returns a boolean value 
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef PREDICATE_FUNCTIONAL_INTERFACE_JPL
#define PREDICATE_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T>
            class Predicate : public FunctionalI{

                protected:

                    /**
                     * @brief The preficate function
                     * @param T type of input
                     */
                    std::function<bool(T)> predicate;

                public:

                    template<typename PredType>
                    Predicate(PredType predicate) : predicate{std::move(predicate)}
                    {

                    }

                    /**
                     * @brief Evaluate the predicate
                     * 
                     * @param t 
                     * @return result
                     */
                    inline bool test(T t){
                        return this->predicate(t);
                    }
            };
        }
    }
}

#endif