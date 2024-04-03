/**
 * @file 
 * 
 * This is the usual implementation of stack using a LIFO method. JPL'stack is a doubled LL similar implementation, de facto
 * it is inherited
 * 
 * @author Gabriele-P03
 * @date 2024-04-03
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef STACK_JPL
#define STACK_JPL

#include "LinkedList.hpp"

namespace jpl{
    namespace _utils{
        namespace _collections{
            namespace _list{
                
                template <typename T>
                class Stack : public LinkedList<T>{
                    
                    private:
                        virtual T get(unsigned long index) const override{
                            T t;
                            Nullable<T>::nullify(t);
                            return t;
                        }

                    public:
                        Stack() : LinkedList<T>(){}
                        Stack(unsigned long size) : LinkedList<T>(size){}
                        Stack(std::initializer_list<T> list): LinkedList<T>(list){}
                        Stack(const Stack* &stack) : Stack<T>(stack->getSize()){

                        }

                        virtual T peek(){
                            
                        }
                        virtual T pop(){
                            
                        }

                        virtual void push(T t){

                        }


                };
            }
        }
    }
}

#endif