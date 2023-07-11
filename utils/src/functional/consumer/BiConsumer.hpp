/**
 * @file 
 * 
 * A Consumer is a void-function which can be passed as a functional interface.
 * Once called, it consume the object which has been passed to it as specified by lambda expression
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef BI_CONSUMER_FUNCTIONAL_INTERFACE_JPL
#define BI_CONSUMER_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T, typename E>
            class BiConsumer : public FunctionalI{

                protected:

                    /**
                     * @brief The consumer function
                     * @param T type of first input
                     * @param E type of second input
                     */
                    std::function<void(T, E)> consumer;

                public:

                    template<typename ConsumeType>
                    BiConsumer(ConsumeType consume) : consumer{std::move(consume)}
                    {

                    }

                    /**
                     * @brief perform the consumer
                     * 
                     * @param t 
                     * @param e 
                     */
                    inline void test(T t, E e){
                        this->consumer(t, e);
                    }
            };
        }
    }
}

#endif