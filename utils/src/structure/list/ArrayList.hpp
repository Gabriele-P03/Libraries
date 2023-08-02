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
 * A copy of the element which is going to be insert is NOT performed, therefore, you oughta do it by yourself
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
                        /**
                         * @brief Left Shift a part of the array list which begins from start 'till last element.
                         * It is used by remove(s) function.
                         * 
                         * @param start first element to be shift. 
                         * @param offset amount of cell to shift
                         * 
                         * @throw IndexOutOfBounds if start - offset is less 0
                         */
                        virtual void leftShiftItems(unsigned int start, unsigned int offset){
                            
                            if(start - offset < 0){
                                throw new IndexOutOfBoundsException(ArrayList, 0, start - offset);
                            }

                            for(unsigned int i = start; i < this->size-1; i++){
                                this->t[i] = this->t[i+1];
                            }
                        }

                    public:

                        ArrayList(unsigned long size) : List<T>(size){
                            if(size > 0)   
                                this->t = new T[size];
                            else
                                this->t = NULL; //Since realloc, if ptr is NULL, behavies as malloc
                        } 
                        ArrayList() : ArrayList<T>(0){} 
                        ArrayList( const ArrayList<T> &arrayList ) : List<T>(arrayList.length()){
                            this->addAll(arrayList);
                        }


                        /**
                         * @brief It performs the reallocating of memory of the current array list
                         * 
                         * @param size amount of elements which will be insert
                        */
                        virtual void reallocate(unsigned long size){
                            this->max = size;
                            this->t = (T*)realloc(this->t, this->max*sizeof(*this->t));
                        }
                        /**
                         * @return the element at the given index
                         * 
                         * @throw IndexOutOfBounds if index is greater or equal than size
                        */
                        virtual T* get(unsigned long index) override{
                            if(index >= this->size)
                                throw new IndexOutOfBoundsException(ArrayList, this->size, index);
                            return &this->t[index];
                        }


                        /**
                         * Insert the given t at the end of the list
                         * 
                         * @param t new element
                        */
                        virtual void add(T t) noexcept {
                            this->add(this->size, t);
                        }
                        /**
                         * Insert the given t at index
                         * 
                         * @param index index
                         * @param t new element
                         * 
                         * @throw IndexOutOfBoundsException if index is greater than max
                        */
                        virtual void add(unsigned long index, T t) override{
                            
                            if(index > this->max)
                                throw new IndexOutOfBoundsException(ArrayList, this->max, index);                   
                            if(index == this->max)
                                this->reallocate(this->max+1);

                            this->rightShiftItems(index, 1);
                            this->t[index] = t;
                            this->size++;
                        }
                        /**
                         * @brief Add the whole given list at the end of this one
                         * 
                         * @param list
                        */
                        virtual void addAll(List<T>* list) noexcept override{
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

                            unsigned long listSize = list->getSize();                
                            if(index + listSize - this->max > 0){
                                this->reallocate(index + listSize - this->max);    //Reallocate as enough
                            }

                            this->rightShiftItems(index, listSize);
                            for(unsigned int i = index; i < index + listSize; i++){
                                this->set(i, *list->get(i-index));
                            }
                            this->size += listSize;
                        }


                        /**
                         * @brief Check into the whole collection if t is present
                         * 
                         * @param t 
                         * @return if t is present
                         */
                        virtual bool contains(T* t) noexcept override{
                            for (unsigned long i = 0; i < this->size; i++)
                                if(t == &this->t[i]) //Address check
                                    return true;
                            return false;
                        }   

                        /**
                         * @brief remove the element at index position from this collection
                         * 
                         * @param index
                         * @throw IndexOutOfBounds if index is greater or equals than size
                         */
                        virtual void remove(unsigned long index) override{
                            
                            if(index >= this->size)
                                throw new IndexOutOfBoundsException(ArrayList, this->max-1, index);

                            T* tmp = &this->t[index];
                            delete tmp;
                            if(index != 0 && index != this->size-1)
                                this->leftShiftItems(index, 1);
                            this->size--;
                            this->reallocate(this->size-1);
                        }
                        /**
                         * @brief remove t from this collection
                         * 
                         * @param t item to remove
                         * @throw NotFoundException if t has not been found into this collection
                         */
                        virtual void remove(T* t) override{
                            for (unsigned long i = 0; i < this->size; i++){
                                if(t == &this->t[i]){
                                    delete this->t;
                                    if(i == 0 && this->size > 1)
                                        this->leftShiftItems(i+1, 1);
                                    this->size--;
                                    this->reallocate(this->max-1);
                                }    
                            }
                            throw new NotFoundException();
                        }
                        /**
                         * @brief remove all collection's items from this collection
                         * 
                         * @param list collection of items to remove
                         * @throw NotFoundException if at least one item into list has not been found
                         */
                        virtual void removeAll(List<T>* list) override{
                            for (unsigned long i = 0; i < this->size; i++){
                                if(t == &this->t[i]){
                                    delete this->t;
                                    if(i == 0 && this->size > 1)
                                        this->leftShiftItems(i+1, 1);
                                    this->size--;
                                    this->reallocate(this->max-1);
                                }    
                            }
                            throw new NotFoundException();
                        }
                        /**
                         * @brief Remove all elements which respect the given predicate
                        */
                        virtual void removeAllIf(_functional::Predicate<T>* predicate) noexcept override{
                            unsigned long count = 0;
                            for (unsigned long i = 0; i < this->size; i++){
                                if(predicate->test(this->t[i])){
                                    delete this->t;
                                    this->t = nullptr;
                                }    
                            }
                            //Re-ordering: substitution all nullptr
                            for(unsigned long i = 0; i < this->size-1; i++){
                                if(&this->t[i] == nullptr){
                                    this->t[i] = this->t[i+1];
                                }
                            }
                            this->size -= count;
                            this->reallocate(this->max-count);
                        }

                        /**
                         * @return the index of the first occurrence of t. 
                         * If t is not found into the list, it returns max
                        */
                        virtual unsigned long firstOccurrence(T* t) override{
                            for(unsigned long i = 0; i < this->size; i++){
                                if(this->t == t)
                                    return i;
                            }
                            return this->max;
                        }
                        /**
                         * @return the index of the last occurrence of t.
                         * If t is not found into the list, it returns max
                        */
                        virtual unsigned long lastOccurrence(T* t) override{
                            for(unsigned long i = this->size-1; i >= 0; i--){
                                if(this->t == t)
                                    return i;
                            }
                            return this->max;
                        }

                        /**
                         * Set t at the given index 
                         * 
                         * @return the previous element which was at index otherwise nullptr if any element has been found at index 
                         * Since ArrayList allows null value, nullptr can be returned even through the list
                         * 
                         * @throw IndexOutOfBounds if index is graeter than or equals than max
                        */
                        virtual T* set(unsigned long index, T t) override{
                            if(index >= this->max)
                                throw new IndexOutOfBoundsException(ArrayList, this->max-1, index);

                            T* tmp = nullptr;
                            if(index < this->size)
                                memcpy(tmp, &this->t[index], sizeof(*this->t));
                            
                            this->t[index] = t;
                            return tmp;
                        }

                        /**
                         * @brief Remove all elements from the list
                        */
                        virtual void clear() override{
                            if(this->size > 0){
                                delete[] this->t;
                                this->size = 0;
                            }
                            this->max = 0;
                        }
                        /**
                         * @return the current array list as a C-style array
                        */
                        virtual const T* toArray() override{
                            T* buffer = nullptr;
                            if(this->size > 0){
                                buffer = new T[this->size];
                                memcpy(buffer, this->t, this->size*sizeof(*this->t));
                            }
                            return buffer;
                        }

                        /**
                         * @return a sub list of the current one. If start is equals to end, am empty list is returned
                         * 
                         * @param start index of the first element to copy
                         * @param end index of the last element to copy (included) 
                         * 
                         * @throw IndexOutOfBounds if start is graeter or equals than end
                         * @throw IndexOutOfBounds if end is graeter or equals than max
                        */
                        virtual ArrayList<T>* subList(unsigned long start, unsigned long end) override{
                            
                            if(end >= this->max){
                                throw new IndexOutOfBoundsException(ArrayList, this->max-1, end);
                            }
                            if(start > end){
                                throw new IndexOutOfBoundsException(ArrayList, end, start);
                            }

                            ArrayList<T>* newOne = new ArrayList<T>(end - start);
                            for(unsigned long i = 0; i < newOne->getSize(); i++){
                                newOne->set(i, this->t[i+start]);
                            }
                            return newOne;
                        }

                        virtual void forEach(_functional::Consumer<T*>* consumer) override{
                            for(unsigned long i = 0; i < this->size; i++)
                                consumer->test(&this->t[i]);                  
                        }
                };
            }
        }
    }
}

#endif