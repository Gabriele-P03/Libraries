/**
 * @file
 * 
 * An ArrayList is a list which elements are consecutive stored as into a vector, but with the difference that an ArrayList is not synchronized  
 * 
 * This type of list is resizeable, but, being an array, if the size exceeds, the whole list is reallocated.
 * When a collection is attempted to being inserted, in order to prevent several reallocating, a unique call is done based on size of the 
 * collection which is going to be inserted
 * 
 * If you need a list which will be manipulated frequently, you should opt to use a LinkedList in order to not perform any reallocating.
 * 
 * Null elements are allowd into this list.
 * 
 * @date 2023-07-12
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
*/

#ifndef ARRAYLIST_JPL
#define ARRAYLIST_JPL

#include "List.hpp"

namespace jpl{

    namespace _utils{

        namespace _collections{

            namespace _list{

                template <typename T>
                class ArrayList : protected List<T>{

                    protected:
                        T* t;

                        /**
                         * @brief It performs the reallocating of memory of the current array list
                         * 
                         * @param size amount of elements which will be insert
                        */
                        virtual inline void reallocate(unsigned long size){
                            this->t = realloc(this->t, (this->size*size)*sizeof(*this->t));
                        }

                    public:

                        template <typename T> ArrayList<T>(unsigned long size) : List<T>(size){
                            if(size > 0){
                                this->t = new T[size];
                            }
                        } 
                        template <typename T> ArrayList<T>() : ArrayList<T>(0){} 
                        template <typename T> ArrayList<T>( ArrayList<T> arrayList ) : List<T>(arrayList.size()){

                        }

                        /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t new element
                         * 
                        */
                        virtual void add(unsigned long index, T* t) noexcept{
                            
                            this->reallocate(1);

                            T* next = this->t[index];
                        }

                        /**
                         * @return the element at the given index
                         * 
                         * @throw IndexOutOfBounds if index is graeter than size()-1 or less than 0
                        */
                        virtual inline T* get(unsigned long index){
                        }

                };
            }
        }
    }
}

#endif