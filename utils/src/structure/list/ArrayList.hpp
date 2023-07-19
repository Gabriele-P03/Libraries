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
 * Null elements are allowed into this list.
 * 
 * A copy of the element which is going to be insert is NOT performed, therefore, you oughta do it by yourself
 * 
 * @date 2023-07-12
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
*/


CONTROLLA LE ADD, POI REMOVE

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
                        virtual void reallocate(unsigned long size){
                            this->max = size;
                            this->t = (T*)realloc(this->t, this->max*sizeof(this->t));
                        }

                        /**
                         * @brief Right Shift a part of the array list which begins from start 'till last element.
                         * It is used by add(s) function.
                         * 
                         * This function is out-of-warnings even on the first insert operation
                         * 
                         * @param start first element to be shift. 
                         * @param offset amount of cell to shift
                         * 
                         * @throw IndexOutOfBounds if start + offset is greater than list's max
                         */
                        virtual void rightShiftItems(unsigned int start, unsigned int offset){
                            
                            if(this->size + offset > this->max){
                                throw new IndexOutOfBoundsException(ArrayList, this->max, this->size+offset);
                            }

                            for(unsigned int i = this->size; i > start; i--){
                                this->t[i+offset-1] = this->t[i-1];
                            }
                        }

                    public:

                        ArrayList(unsigned long size) : List<T>(size){
                            if(size > 0){
                                this->t = new T[size];
                            }
                        } 
                        ArrayList() : ArrayList<T>(0){} 
                        ArrayList( const ArrayList<T> &arrayList ) : List<T>(arrayList.length()){}

                        /**
                         * Insert the given t at the end of the list
                         * 
                         * @param t new element
                        */
                        virtual const void add(T* t) noexcept {
                            this->add(this->size, t);
                        }
                        /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t new element
                         * 
                         * @throw IndexOutOfBounds if index is greater or equal to list's size
                        */
                        virtual void add(unsigned long index, T* t) override{
                            
                            if(index > this->max)
                                throw new IndexOutOfBoundsException(ArrayList, this->size, index);                   
                            if(index == this->max)
                                this->reallocate(this->max+1);

                            this->rightShiftItems(index, 1);
                            this->t[index] = t;
                            this->size++;
                        }
                        virtual void addAll(List<T>* list) override{
                            this->addAll(this->size, list);
                        }
                        /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t collection of new elements
                         * 
                         * @throw IndexOutOfBounds if index is greater or equal to list's size
                        */
                        virtual void addAll(unsigned long index, List<T>* list) override{
                            
                            if(index > this->max)
                                throw new IndexOutOfBoundsException(ArrayList, this->size, index); 

                            unsigned long listSize = list->size();                  
                            if(index == this->max)
                                this->reallocate(this->max+listSize);

                            this->rightShiftItems(index, listSize);
                            for(unsigned int i = index; i < index + listSize; i++){
                                this->t[i] = list->get(i);
                            }
                            this->size += listSize;
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