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

#ifndef CONSUMER_FUNCTIONAL_INTERFACE_JPL
#define CONSUMER_FUNCTIONAL_INTERFACE_JPL

#include "../FunctionalInterface.hpp"

namespace jpl{

    namespace _utils{

        namespace _functional{

            template<typename T>
            class Consumer : public FunctionalI{

                protected:

                    /**
                     * @brief The consumer function
                     * @param T type of input
                     */
                    std::function<void(T)> consumer;

                public:

                    template<typename ConsumeType>
                    Consumer(ConsumeType consume) : consumer{std::move(consume)}
                    {

                    }

                    /**
                     * @brief perform the consumer
                     * 
                     * @param t 
                     */
                    inline void test(T t){
                        this->consumer(t);
                    }
            };
        }
    }
}

#endif