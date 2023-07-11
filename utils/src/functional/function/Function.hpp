/**
 * @file 
 * 
 * A Function is a trailing return-function which can be passed as a functional interface.
 * Once called, it consume the object which has been passed to it as specified by lambda expression and then
 * return a value whose type has been declared via template
 * 
 * @date 2023-05-28
 * @author Gabriele-P03
 */

#ifndef FUNCTION_FUNCTIONAL_INTERFACE_JPL
#define FUNCTION_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T, typename R>
            class Function : public FunctionalI{

                protected:

                    /**
                     * @brief The Function function
                     * @param T type of input
                     * @param R type of return
                     */
                    std::function<R(T)> function;

                public:

                    template<typename FunctionType>
                    Function(FunctionType function) : function{std::move(function)}
                    {

                    }

                    /**
                     * @brief perform the function
                     * 
                     * @param t 
                     * 
                     * @return R
                     */
                    inline R test(T t){
                        return this->function(t);
                    }
            };
        }
    }
}

#endif