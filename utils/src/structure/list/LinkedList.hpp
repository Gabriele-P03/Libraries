/**
 * @file
 * 
 * A linked list is an ordered collection of nodes which - probably - are not sequentially stored 
 * in memory due to available space during insertion time
 * 
 * A node is a struct which contains the element T, a pointer to the previous node and a pointer 
 * to the next one; thus, this is actually a Double and Circular Linked List as described by DSA.
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
                        Node(){}
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

                    Node* smartProbe(unsigned long index) const{
                        if( index <= (this->size/2) ){
                            return this->forwardProbe(index);
                        }                                
                        return this->reverseProbe(this->size-index-1);
                    }

                public:

                    LinkedList() : List<T>(){
                        this->head = nullptr;
                        this->tail = nullptr;
                    }
                    LinkedList(Collection<T>* collection) : List<T>(collection->getSize()){
                        this->head = nullptr;
                        this->tail = nullptr;
                        this->addAll(collection);
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
                            return this->smartProbe(index)->element;
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
                            Node* tmp = this->smartProbe(index);
                            newNode->previous = tmp;
                            newNode->next = tmp->next;
                            tmp->next = newNode;
                            tmp->next->previous = newNode;
                            tmp = newNode;
                        }
                        this->size++;
                    }

                    virtual void add(const T &t) noexcept override{
                        this->add(this->size, t);
                    }


                    virtual bool contains(const T t) const noexcept override{
                        Node* cr = this->head;
                        for(unsigned long i = 0; i < this->size; i++){
                            if(cr->element == t){
                                return true;
                            }
                            cr = cr->next;
                        }
                        return false;
                    }
                    virtual void clear() noexcept override{
                        Node* cr = this->head;
                        for(unsigned long i = 0; i < this->size; i++){
                            delete cr;
                            cr = cr->next;
                        }   
                        this->size = 0;
                    }
                    virtual void addAll(unsigned long index, Collection<T>* collection) override{
                        if(collection == nullptr){
                            throw new _exception::NullPointerException("Collection passed to addAll cannot be nullptr");
                        }
                        unsigned long size = collection->getSize();
                        Node* buffer = new Node[size]();
                        unsigned long i = 0;
                        collection->forEach( [&](T t){
                            if(i < size-1){
                                buffer[i].next = &buffer[i+1];
                            }
                            if(i > 0){
                                buffer[i].previous = &buffer[i-1];
                            }
                            buffer[i++].element = t;
                        });
                        if(this->size == 0){
                            this->head = buffer;
                            this->tail = &buffer[size-1];   //It is safe even when collection has one item
                        }else{

                        }
                    }
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

                    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T> &list){
                        for(unsigned long i = 0; i < list.size; i++){
                            Printable<T>::print(os, list.get(i));
                        }
                        return os;
                    }                    
            };
        }
    }
}

#endif