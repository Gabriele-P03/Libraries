/**
 * @file 
 * 
 * A supplier is a typed-function which can be passed as a functional interface.
 * It does not accept any arguments as input, but it returns an object evaluated by its lambda expression
 * 
 * @date 2023-05-28
 * @author Gabriele-P03
 */

#ifndef SUPPLIER_FUNCTIONAL_INTERFACE_JPL
#define SUPPLIER_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T>
            class Supplier : public FunctionalI{

                protected:

                    /**
                     * @brief The supplier function
                     * @param T type of return
                     */
                    std::function<T()> supplier;

                public:

                    template<typename SupplyType>
                    Supplier(SupplyType supplier) : supplier{std::move(supplier)}
                    {

                    }

                    /**
                     * @brief Evaluate the predicate
                     * 
                     * @param t 
                     * @return result
                     */
                    inline T test(){
                        return this->supplier();
                    }
            };
        }
    }
}

#endif