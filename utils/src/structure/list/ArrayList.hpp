/**
 * @file
 * 
 * An ArrayList is a list which elements are consecutive stored as into a vector
 * 
 * This type of list is resizeable, but, being an array, if the size exceeds, the whole list is reallocated.
 * When a collection is attempted to being inserted, in order to prevent several reallocating, a unique call is done 
 * based on size of the collection which is going to be inserted.
 * If you know that several amount of calls are going to be done to add() - and you know how many 
 * elements are going to be - then you should call reallocate() by yourself, preventing the same several amount
 * of calls to the function 
 * 
 * If you need a list which will be manipulated frequently, you should opt to use a LinkedList in order to not perform 
 * any reallocating.
 * 
 * Null elements are allowed into this.
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
                                this->list[i] = this->list[i+offset];
                            }
                        }

                    public:

                        ArrayList() : List<T>(){} 
                        ArrayList(const T* const array, unsigned long size){
                            if(array == nullptr){
                                throw new _exception::IllegalArgumentException("You cannot pass a null pointer");
                            }else{
                                if(size == 0){
                                    throw new _exception::IllegalArgumentException("You have passed a size parameter as 0");
                                }
                            }
                            this->size = size;
                            this->max = size;
                            this->list = new T[this->size];
                            memcpy(this->list, array, sizeof(T)*this->size);
                        }
                        ArrayList(std::initializer_list<T> ls) : ArrayList<T>(){
                            this->reallocate(ls.size());
                            for(unsigned long i = 0; i < this->max; i++){
                                this->list[i] = ls.begin()[i];
                            }
                            this->size = ls.size();
                        }
                        ArrayList(List<T>* list) : List<T>(list){
                            this->addAll(list);
                        }

                        /**
                         * @brief It performs the reallocating of memory of the current array list
                         * 
                         * @param size amount of elements which will be insert
                        */
                        virtual void reallocate(unsigned long size){
                            this->max = size;
                            if(this->size == 0){
                                this->list = new T[size];
                            }else{
                                this->list = (T*)realloc(this->list, this->max*sizeof(T));
                            }
                        }


                        virtual T &get(unsigned long index) const override{
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


                        virtual void addAll(unsigned long index, List<T>* list) override{
                            if(list == nullptr){
                                throw new _exception::NullPointerException("Collection passed to addAll cannot be nullptr");
                            }
                            
                            if(index+list->getSize() > this->max){
                                this->reallocate(index+list->getSize()-this->max);
                            }

                            if(index < this->size)
                                this->rightShiftItems(list->getSize(), 1);

                            for(unsigned long i = 0; i < list->getSize(); i++){
                                this->list[index+i] = list->get(i);
                            }

                            this->size += index + list->getSize() - this->size;
                        }

                        virtual void addAll(List<T>* list) noexcept override{
                            this->addAll(this->size, list);
                        }


                        virtual bool contains(const T t) const noexcept override{
                            for(unsigned long i = 0; i < this->size; i++){
                                if( this->list[i] == t ){
                                    return true;
                                }
                            }
                            return false;
                        } 

                        virtual void removeAt(unsigned long index) override{
                            if(index >= this->size){
                                throw new jpl::_exception::IndexOutOfBoundsException(this->size, index);
                            }
                            T &t = this->list[index];
                            jpl::_utils::Ereaseable<T>::erease(t);
                            this->leftShiftItems(0, 1);
                            this->reallocate(--this->size);
                        }
                        virtual void remove(T t) override{
                            for(unsigned long i = 0; i < this->size; i++){
                                T &cr = this->list[i];
                                if( cr == t ){
                                    jpl::_utils::Ereaseable<T>::erease(t);
                                    this->leftShiftItems(i, 1);
                                    this->reallocate(--this->size);
                                    return;
                                }
                            }
                            throw new jpl::_exception::NotFoundException( jpl::_utils::Printable<T>::to_string(t) + " has not been found into the list");
                        }  
   
                        virtual void removeAll(List<T>* list) override{
                            for(unsigned long i = 0; i < list->getSize(); i++){
                                T &ls = list->get(i);
                                bool flag = false;
                                for(unsigned long j = 0; j < this->size; j++){
                                    T cr = this->list[j];
                                    if(ls == cr){
                                        jpl::_utils::Ereaseable<T>::erease(cr);
                                        this->leftShiftItems(j, 1);
                                        this->size--;
                                        flag = true;
                                        j--;
                                        if(std::is_pointer<T>::value){
                                            Nullable<T>::nullify(ls);
                                        }
                                        break;
                                    }
                                }
                                if(!flag)
                                    throw new jpl::_exception::NotFoundException( jpl::_utils::Printable<T>::to_string(ls) + " has not been found into list");
                            }
                            this->reallocate(this->size);
                        }
                        virtual void removeAllIf(_functional::Predicate<T> predicate) noexcept override{
                            bool flag = false;  //It is used to check if at least an element has been removed
                            for(unsigned long i = 0; i < this->size; ){
                                T &t = this->list[i];
                                if(predicate.test(t)){
                                    jpl::_utils::Ereaseable<T>::erease(t);
                                    this->leftShiftItems(i, 1);
                                    this->size--;
                                    if(!flag)
                                        flag = true;
                                }else{
                                    i++;
                                }
                            } 
                            if(flag){
                                this->reallocate(this->size);
                            }
                        }

                        virtual T set(unsigned long index, const T &t) override {
                            if(index > this->size){
                                throw new _exception::IndexOutOfBoundsException(this->size, index);
                            }
                            T &cr = this->list[index];
                            T buffer;
                            Copyable<T>::copy(buffer, cr);
                            Ereaseable<T>::erease(cr);
                            cr = t;
                            return buffer;
                        } 

                        virtual ArrayList<T>* subList(unsigned long start, unsigned long end) const override{
                            if(start >= this->size)
                                throw new _exception::IndexOutOfBoundsException(this->size, start, "Start is larger/equals than list's size");
                            if(end >= this->size)
                                throw new _exception::IndexOutOfBoundsException(this->size, end, "End is larger/equals than list's size");               
                            if(start > end)
                                throw new _exception::IndexOutOfBoundsException(end, start, "Start is larger than End"); 
                            ArrayList<T>* buffer = new ArrayList<T>();
                            buffer->reallocate(end-start);
                            for(unsigned long i = start; i < end; i++){
                                T &cr = this->list[i];
                                buffer->add(cr);
                            }
                            return buffer;
                        }
                        virtual ArrayList<T>* subList(unsigned long start) const override{
                            return this->subList(start, this->size);
                        }

                        virtual unsigned long firstOccurrence(T t) const noexcept override{ 
                            for(unsigned long i = 0; i < this->size; i++){
                                if(this->list[i] == t)
                                    return i;
                            }
                            return this->max;
                        }
                        virtual unsigned long lastOccurrence(T t) const noexcept override{ 
                            for(unsigned long i = this->size-1; i >= 0; i--){
                                if(this->list[i] == t)
                                    return i;
                            }
                            return this->max;
                        }

                        virtual void clear() noexcept override{
                            Ereaseable<T>::v_erease(this->list, this->size);
                            delete[] this->list;
                            this->size = 0;
                            this->max = 0;
                        }


                        virtual T* toArray() const noexcept override {
                            T* buffer = new T[this->size];
                            memcpy(buffer, this->list, sizeof(T)*this->size);
                            return buffer;
                        }

                        virtual void forEach(_functional::Consumer<T> consumer) {
                            for(unsigned long i = 0; i < this->size; i++){
                                consumer.test(this->list[i]);
                            }
                        }

                        virtual void compress() noexcept override{
                            unsigned long c = 0;
                            unsigned long firstNull = this->size;
                            for(unsigned long i = 0; i < this->size; i++){
                                T t = this->list[i];
                                if(Nullable<T>::isNull(t)){
                                    if(firstNull == this->size){
                                        firstNull = i;
                                    }
                                }else{
                                    if(firstNull != this->size){
                                        unsigned long offset = i-firstNull;
                                        this->leftShiftItems(firstNull, offset);
                                        this->size -= offset;
                                        firstNull = this->size;
                                        i -= offset;
                                    }
                                }
                            }
                            if(firstNull != this->size){
                                unsigned long offset = this->size-firstNull;
                                this->leftShiftItems(firstNull, offset);
                                this->size -= offset;
                            }
                        }

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