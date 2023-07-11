/**
 * @file 
 * 
 * A Bi-Function is a trailing return-function which can be passed as a functional interface.
 * Once called, it consume the two object which have been passed to it as specified by lambda expression 
 * and then return a value whose type has been declared via template
 * 
 * @date 2023-05-28
 * @author Gabriele-P03
 */

#ifndef BI_FUNCTION_FUNCTIONAL_INTERFACE_JPL
#define BI_FUNCTION_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T, typename E, typename R>
            class BiFunction : public FunctionalI{

                protected:

                    /**
                     * @brief The Function function
                     * @param T type of first input
                     * @param E type of second input
                     * @param R type of return
                     */
                    std::function<R(T, E)> function;

                public:

                    template<typename FunctionType>
                    BiFunction(FunctionType function) : function{std::move(function)}
                    {

                    }

                    /**
                     * @brief perform the function
                     * 
                     * @param t 
                     * @param e
                     * 
                     * @return R
                     */
                    inline R test(T t, E e){
                        return this->function(t, e);
                    }
            };
        }
    }
}

#endif