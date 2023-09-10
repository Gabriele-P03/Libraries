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
#include <memory>

namespace jpl{

    namespace _utils{

        namespace _collections{

            namespace _list{

                template <typename T>
                class ArrayList : public List<T>{

                    protected:
                        T* list;

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
                            
                            if(start > this->max){
                                throw new jpl::_exception::IndexOutOfBoundsException(this->max, this->size+offset);
                            }
                            if(this->size + offset > this->max){
                                this->reallocate(this->max + this->max - this->size + offset);
                            }

                            for(unsigned int i = this->size; i > start; i--){
                                this->list[i+offset-1] = this->list[i-1];
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
                                throw new jpl::_exception::IndexOutOfBoundsException(0, start - offset);
                            }

                            for(unsigned int i = start; i < this->size-1; i++){
                                this->list[i] = this->list[i+1];
                            }
                        }

                    public:

                        ArrayList(unsigned long size) : List<T>(size){
                            if(size > 0)   
                                this->list = new T[size];
                            else
                                this->list = nullptr; //Since realloc, if ptr is nullptr, behavies as malloc
                        } 
                        ArrayList() : ArrayList<T>(0UL){} 
                        ArrayList( const ArrayList<T>* arrayList ){
                            //this->addAll(arrayList);
                        }

                        ArrayList(std::initializer_list<T> ls) : ArrayList<T>(ls.size()){
                            for(unsigned long i = 0; i < this->max; i++){
                                this->list[i] = ls.begin()[i];
                            }
                        }


                        /**
                         * @brief It performs the reallocating of memory of the current array list
                         * 
                         * @param size amount of elements which will be insert
                        */
                        virtual void reallocate(unsigned long size){
                            this->max = size;
                            this->list = (T*)realloc(this->list, this->max*sizeof(*this->list));
                        }


                        virtual T &get(unsigned long index){
                            if(index >= this->size){
                                throw new jpl::_exception::IndexOutOfBoundsException(this->size, index);
                            }
                            return this->list[index];
                        }


                        virtual void add(unsigned long index, const T &t) override{
                            if(index >= this->max){
                                this->reallocate(index+1);
                            }
                            this->list[index] = t;
                            if(index <= this->size){
                                this->size++;
                            }else{
                                this->size = index+1;
                            }
                        }

                        virtual void add(const T &t) noexcept override{
                            this->add(this->size, t);
                        }


                        virtual void addAll(unsigned long index, List<T>* &list) noexcept override{
                            if(index+list->getSize() >= this->max){
                                this->reallocate(index+list->getSize()+1-this->max);
                            }

                            for(unsigned int i = 0; i < list->getSize(); i++){
                                this->list[index+i] = list->get(i);
                            }
                        }

                        virtual void addAll(List<T>* &list) noexcept override{
                            this->addAll(this->size, list);
                        }


                        virtual bool contains(const T &t) const noexcept override{return false;} 

                        virtual void removeAt(unsigned long index) override{}
                        virtual void remove(T t) override{}  
                        virtual void removeAll(const List<T>* list) override{}
                        virtual void removeAllIf(_functional::Predicate<T>* predicate) noexcept override{}

                        virtual T* set(unsigned long index, const T &t) override {return nullptr;} 

                        virtual List<T>* subList(unsigned long start, unsigned long end) const override{return nullptr;}
                        virtual List<T>* subList(unsigned long start) const override{return nullptr;}

                        virtual unsigned long firstOccurrence(T* t) const noexcept override{return 0;}
                        virtual unsigned long lastOccurrence(T* t) const noexcept override{ return 0;}

                        virtual void clear() noexcept override{}
                        virtual T* toArray() const noexcept override {return nullptr;}

                        virtual void forEach(_functional::Consumer<T*>* consumer) {}

                        friend std::ostream& operator<<(std::ostream& os, const ArrayList<T> &list){
                            for(unsigned long i = 0; i < list.size; i++){
                                Printable<T>::print(os, list.list[i]);
                            }
                            return os;
                        }
                };
            }
        }
    }
}

#endif