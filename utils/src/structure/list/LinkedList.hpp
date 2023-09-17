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

                    struct Node{

                        T element;
                        Node* previous;
                        Node* next;

                        Node(const T &element, Node* next, Node* previous){
                            this->element = element;
                            this->next = next;
                            this->previous = previous;
                        }
                        Node(const T &element) : Node(element, nullptr, nullptr){}

                        ~Node(){
                            Ereaseable<T>::erease(this->element);
                        }
                    };

                    Node *head, *tail;

                    Node* forwardProbe(unsigned long steps) const {
                        if( steps >= this->size )
                            throw new _exception::IndexOutOfBoundsException(this->size, steps);
                        Node* node = head;
                        for(unsigned long i = 0; i < steps; i++){
                            node = node->next;
                        }
                        return node;
                    }
                    Node* reverseProbe(unsigned long steps) const{
                        if( steps >= this->size )
                            throw new _exception::IndexOutOfBoundsException(this->size, steps);
                        Node* node = tail;
                        for(unsigned long i = steps; i > 0; i--){
                            node = node->previous;
                        }
                        return node;
                    }

                public:

                    LinkedList() : List<T>(){
                        this->head = nullptr;
                        this->tail = nullptr;
                    }
                    LinkedList(Collection<T>* list) : List<T>(list->getSize()){
                        this->head = nullptr;
                        this->tail = nullptr;
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

                    virtual void add(unsigned long index, const T &t) override{
                        if(index > this->size){
                            throw new _exception::IndexOutOfBoundsException(this->size, index);
                        }
                        Node* newNode = new Node(t);
                        if(index == 0){ //head
                            if(this->size != 0){//LL not empty
                                this->head->previous = newNode;
                                newNode->next = this->head;
                            }else{//If LL is empty, head is equal to tail
                                this->tail = newNode;
                            }
                            this->head = newNode;
                        }else if(index == this->size){//Tail
                            this->tail->next = newNode;
                            newNode = this->tail;
                            this->tail = newNode;
                        }else{
                            if(index <= this->size/2){
                                Node* tmp = this->forwardProbe(index-1);
                                newNode->previous = tmp->previous;
                                newNode->next = tmp;
                                tmp->previous->next = newNode;
                                tmp->previous = newNode;
                                tmp = newNode;
                            }else{
                                Node* tmp = this->reverseProbe(this->size-index);
                                newNode->next = tmp;
                                newNode->previous = tmp->previous; 
                                tmp->previous->next = newNode;
                                tmp->next = newNode;
                            }

                        }
                        this->size++;
                    }

                    virtual void add(const T &t) noexcept override{
                        this->add(this->size, t);
                    }


                    virtual bool contains(const T t) const noexcept override{return false;}
                    virtual void clear() noexcept override{}
                    virtual void addAll(unsigned long index, Collection<T>* collection) override{}
                    virtual void addAll(Collection<T>* collection) override{} 
                    virtual unsigned long firstOccurrence(T t) const noexcept override {return 0;}
                    virtual unsigned long lastOccurrence(T t) const noexcept override {return 0;}
                    virtual void removeAt(unsigned long index) override{}
                    virtual void remove(T t) override{}                    
                    virtual void removeAll(Collection<T>* collection) override{}
                    virtual void removeAllIf(_functional::Predicate<T> predicate) noexcept override{}
                    virtual T set(unsigned long index, const T &t) override {return NULL;}
                    virtual List<T>* subList(unsigned long start, unsigned long end) const override {return NULL;}
                    virtual List<T>* subList(unsigned long start) const override {return NULL;}
                    virtual void forEach(_functional::Consumer<T> consumer) override {}
                    virtual T* toArray() const noexcept override{return NULL;}
            };
        }
    }
}

#endif