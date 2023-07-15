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
                            this->t = (T*)realloc(this->t, (this->size+size)*sizeof(*this->t));
                        }

                    public:

                        ArrayList(unsigned long size) : List<T>(size){
                            if(size > 0){
                                this->t = new T[size];
                            }
                        } 
                        ArrayList() : ArrayList<T>(0){} 
                        ArrayList( const ArrayList<T> &arrayList ) : List<T>(arrayList.length()){

                        }

                        /**
                         * Insert the given t 
                         * 
                         * @param t new element
                        */
                        virtual const void add(T* t) noexcept {
                            this->add(0, t);
                        }

                        /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t new element
                         * 
                         * @throw IndexOutOfBounds if index is greater or equal to list's size
                        */
                        virtual const void add(unsigned long index, T* t){
                            
                            if(index >= this->size()){
                                throw new IndexOutOfBoundsException(ArrayList, this->size, index);
                            }

                            this->reallocate(1);

                            T next = this->t[index];
                            this->t = t;
                            this->t[index+1] = next;
                        }
                                                /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t collection of new elements
                         * 
                         * @throw IndexOutOfBounds if index is greater or equal to list's size
                        */
                        virtual const void addAll(unsigned long index, Collection<T>* list){
                            
                            if(index >= this->size()){
                                throw new IndexOutOfBoundsException(ArrayList, this->size, index);
                            }

                            this->reallocate(list->size());

                            T next = this->t[index];
                            this->t = list;
                            this->t[index+1] = next;
                        }



                        /**
                         * @return the element at the given index
                         * 
                         * @throw IndexOutOfBounds if index is graeter than length()-1 or less than 0
                        */
                        virtual inline T* get(unsigned long index) override{

                            if(index >= this->size){
                                throw new IndexOutOfBoundsException(ArrayList, this->size, index);
                            }

                            return &this->t[index];
                        }

                        virtual void forEach(_functional::Consumer<T*> consumer){
                            for(unsigned int i = 0; i < this->size; i++){
                                consumer.test(&this->t[i]);
                            }
                        }
                };
            }
        }
    }
}

#endif