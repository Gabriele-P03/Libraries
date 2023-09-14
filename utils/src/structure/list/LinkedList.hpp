/**
 * @file
 * 
 * A linked list is an ordered collection of nodes which - probably - are not sequentially stored 
 * in memory due to available space during insertion time
 * 
 * A node is a struct which contains the element T, a pointer to the previous node and a pointer 
 * to the next one; thus, this is actually a Double Linked List as described by DSA.
 * The first node is called also Head and the last one Tail.
 * Being a DLL, insertion is O(1) only when it is done either at head or tail of it, otherwise is O(n).
 * Searching is always O(n).
 * Indexed Deletion - removeAt(ulong) - is just like Insertion; Smooth one - remove(T) - is O(n).
 * 
 * Just like ArrayList, if you declare a Linked List of pointer, no new object will be allocated
 * 
 * @date 14-09-2023
 * @author Gabriele-P03
*/
#ifndef LINKED_LIST_JPL
#define LINKED_LIST_JPL

#include "List.hpp"

namespace jpl{
    namespace _utils{
        namespace _collection{

            template<typename T>
            class LinkedList : public List<T>{

                private:

                    typedef struct{

                        T element;
                        T* previous;
                        T* next;

                    }Node;

                    Node *head, *tail;

                public:

                    LinkedList() : List<T>(0UL){}

                    LinkedList(const LinkedList* const list) : List<T>(list->getSize()){

                    }

                    LinkedList(const T* array, unsigned long size){
                        if(array == nullptr){
                            throw new _exception::NullPointerException("You cannot pass a null pointer");
                        }else{
                            if(size == 0){
                                throw new _exception::IllegalArgumentException("A pointer is not nullptr but size is 0");
                            }
                        }
                        this->duplicateElements = true;
                        this->nullableElements = true;
                        this->size = size;
                        this->max = size;
                    } 

                    virtual T &get(unsigned long index) const override{
                        if(index >= this->size){
                            throw new _exception::IndexOutOfBoundsException(this->size, index);
                        }
                        if(index == 0)
                            return *this->head;
                        else if(index == this->size-1)
                            return *this->tail;
                        else
                            //O(n)
                    }
            };
        }
    }
}

#endif