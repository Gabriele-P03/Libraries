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
        namespace _collections{

            template<typename T>
            class LinkedList : public List<T>{

                protected:

                    typedef struct{

                        T element;
                        T* previous;
                        T* next;

                    }Node;

                    Node *head, *tail;

                    Node* forwardProbe(unsigned long steps){
                        if( steps >= this->size )
                            throw new _exception::IndexOutOfBoundsException(this->size, steps);
                        Node* node = head;
                        for(unsigned long i = 0; i < steps; i++){
                            node = node->next;
                        }
                        return node;
                    }
                    Node* reverseProbe(unsigned long steps){
                        if( steps >= this->size )
                            throw new _exception::IndexOutOfBoundsException(this->size, steps);
                        Node* node = tail;
                        for(unsigned long i = steps; i > 0; i--){
                            node = node->previous;
                        }
                        return node;
                    }

                public:

                    LinkedList() : List<T>(0UL){}
                    LinkedList(Collection<T>* list) : List<T>(list->getSize()){
                        this->addAll(list);
                    }

                    virtual T &get(unsigned long index) const override{
                        if(index >= this->size){
                            throw new _exception::IndexOutOfBoundsException(this->size, index);
                        }
                        if(index == 0){
                            return this->head->element;
                        }else if(index == this->size-1){
                            return this->tail->element;
                        }else{
                            if( index < (this->size/2) ){
                                return this->forwardProbe(index)->element;
                            }                                
                            return this->reverseProbe(index)->element;
                        }
                    }
            };
        }
    }
}

#endif