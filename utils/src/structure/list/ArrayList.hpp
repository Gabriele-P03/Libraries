/**
 * @file
 * 
 * An ArrayList is a list which elements are consecutive stored as into a vector, but with the difference that an ArrayList is not synchronized  
 * 
 * This type of list is resizeable, but, being an array, if the size exceeds, the whole list is reallocated.
 * When a collection is attempted to being inserted, in order to prevent several reallocating, a unique call is done based on size of the 
 * collection which is going to be inserted.
 * If you know that several amount of calls are going to be done to either add() or addAll() - and you know how many 
 * elements are going to be insert - then you should call reallocate() by yourself, preventing the same several amount
 * of calls to the function 
 * 
 * If you need a list which will be manipulated frequently, you should opt to use a LinkedList in order to not perform any reallocating.
 * 
 * Null elements are allowed into this list.
 * 
 * ArrayList does not implements any borderline about max amount of elements which can be contained into it
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
                class ArrayList : public List<T>{

                    protected:
                        T* t;

                    public:

                        ArrayList(unsigned long size) : List<T>(size){
                            if(size > 0)   
                                this->t = new T[size];
                            else
                                this->t = NULL; //Since realloc, if ptr is NULL, behavies as malloc
                        } 
                        ArrayList() : ArrayList<T>(0){} 
                        ArrayList( const ArrayList<T> &arrayList ) : List<T>(arrayList.length()){}

                        /**
                         * @brief Insert t into the structure. The position where t is pushed depends
                         * by the type of structure
                         * 
                         * @param t 
                         * 
                         */
                        virtual void add(T* t) override{
                            if(this->size+1 > this->max){
                                this->reallocate(this->max+1);
                            }
                            this->size += 1;
                            this->t[this->size] = t;
                        }
                        /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t new element
                         * 
                         * @throw NullPointerException if list does not permit null elements and t it is
                        */
                        virtual void add(unsigned long index, T* t) override{
                            if(index > this->max){
                                this->reallocate(this->max+this->max-index);
                            }else if(this->size+1 > this->max){
                                this->reallocate(this->max+1);
                            }

                        }
                        /**
                         * @brief Insert into the structure all items contained into list at the end
                         * if the array list
                         * 
                         * @param list 
                         */
                        virtual void addAll(Collection<T> *list){
                            unsigned long max1 = this->max+list->size;
                            if(list->size > max1){
                                this->reallocate(max1);
                            }
                        };


                        virtual void removeAllIf(_functional::Predicate<T>* predicate) override{
                            for(unsigned long i = 0; i < this->size; i++){
                                if(predicate->test(this->t[i])){
                                    delete this->t[i];
                                }
                            }
                                  
                        }


                        virtual void clear() override{
                            if(this->size > 0){
                                delete[] this->t;
                            }
                        }

                        virtual const T* toArray() override{
                            T* buffer = nullptr;
                            if(this->size > 0){
                                buffer = new T[this->size];
                                memcpy(buffer, this->t, this->size*sizeof(this->t));
                            }
                            return buffer;
                        }

                        virtual void forEach(_functional::Consumer<T*>* consumer) override{
                            for(unsigned long i = 0; i < this->size; i++)
                                consumer->test(this->t[i]);                  
                        }


                        /**
                         * @brief Reallocate the arrayList
                         * 
                         * @param size new size of the list (set, not added)
                        */
                        virtual void reallocate(unsigned long size){
                            this->max = size;
                            T* tmp = (T*)realloc(this->t, this->max*sizeof(t));

                            if(tmp == nullptr){
                                throw new OutOfMemoryException(ArrayList, " could not be reallocated");
                            }else{
                                this->t = tmp;
                            }
                        }
                };
            }
        }
    }
}

#endif