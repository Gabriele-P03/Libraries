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
            namespace _list{
                

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
                            if(index >= this->size){
                                throw new _exception::IndexOutOfBoundsException(this->size-1, attempted);
                            }
                            if( index <= (this->size/2) ){
                                return this->forwardProbe(index);
                            }                                
                            return this->reverseProbe(this->size-index-1);
                        }

                        /**
                         * @brief
                         * It detaches the given node attaching the previous one with the next one.
                         * It is a smart function wich checks if it is either the head or tail of the LL.
                         * You must pass a node whose element had been already deleted   
                         * 
                         * @throw NullPointer if node is nullptr
                        */
                        void detach(Node* &node){
                            if(node == nullptr)
                                throw new _exception::NullPointerException("A nullptr cannot be passed");                           
                            if(node->previous != nullptr){  //not head
                                if(node->next != nullptr){  //not tail
                                    node->previous->next = node->next;
                                    node->next->previous = node->previous;
                                }else{//tail -> new tail
                                    node->previous->next = nullptr;
                                    this->tail = node->previous;
                                }
                            }else{  //head -> new head
                                if(node->next != nullptr){
                                    node->next->previous = nullptr;
                                    this->head = node->next;
                                }
                            }
                        }

                        /**
                         * It detaches all nodes among first and last (both included)
                         * You must be sure that all nodes from first to last are deleted
                        */
                        void detach_s(Node* &first, Node* &last, unsigned long size){
                            if(first == this->head){
                                if(last != this->tail){
                                    last->next->previous = nullptr;
                                    this->head = last->next;
                                    this->size -= size;
                                }else{
                                    this->head = nullptr;
                                    this->tail = nullptr;
                                    this->size = 0;
                                }
                            }else{
                                if(last != this->tail){
                                    first->previous->next = tail->next;
                                    tail->next->previous = first->previous;
                                }else{
                                    first->previous->next = nullptr;
                                    this->tail = first->previous;
                                }
                                this->size -= size;
                            }
                        }

                    public:

                        LinkedList() : List<T>(){
                            this->head = nullptr;
                            this->tail = nullptr;
                        }
                        LinkedList(List<T>* list) : List<T>(list->getSize()){
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
                        virtual void addAll(unsigned long index, List<T>* list) override{
                            if(list == nullptr){
                                throw new _exception::NullPointerException("list passed to addAll cannot be nullptr");
                            }
                            unsigned long size = list->getSize();
                            Node* buffer = new Node[size]();
                            unsigned long i = 0;
                            list->forEach( [&](T t){
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
                                if(index == 0){
                                    this->head->previous = &buffer[size-1];
                                    buffer[size-1].next = this->head;
                                    this->head = buffer;
                                }else if(index == this->size){
                                    this->tail->next = buffer;
                                    buffer[0].previous = this->tail;
                                    this->tail = &buffer[size-1]; 
                                }else{
                                    Node* cr = this->smartProbe(index);
                                    buffer->previous = cr;
                                    buffer[size-1].next = cr->next;
                                    cr->next->previous = &buffer[size-1];
                                    cr->next = buffer;
                                }
                            }
                            this->size += size;
                        }
                        virtual void addAll(List<T>* list) override{
                            this->addAll(this->size, list);
                        } 
                        virtual unsigned long firstOccurrence(T t) const noexcept override {
                            Node* cr = this->head;
                            for(unsigned long i = 0; i < this->size; i++){
                                if(cr->element == t)
                                    return i;
                                cr = cr->next;
                            }
                            return this->size;
                        }
                        virtual unsigned long lastOccurrence(T t) const noexcept override {
                            Node* cr = this->tail;
                            for(unsigned long i = this->size; i > 0; i--){
                                if(cr->element == t)
                                    return i-1;
                                cr = cr->previous;
                            }
                            return this->size;
                        }
                        virtual void removeAt(unsigned long index) override{
                            Node* cr = this->smartProbe(index);
                            Ereaseable<T>::erease(cr->element);
                            this->detach(cr);
                            this->size--;
                        }
                        virtual void remove(T t) override{
                            Node* cr = this->head;
                            for(unsigned long i = 0; i < this->size; i++){
                                if(cr->element == t){
                                    Ereaseable<T>::erease(cr->element);
                                    this->detach(cr); 
                                    this->size--;
                                    return;
                                }
                                cr = cr->next;
                            }
                        }                    
                        virtual void removeAll(List<T>* list) override{
                            Node* cr = this->head;
                            Node* firstDeleted = nullptr;
                            unsigned long len = 0;
                            for(unsigned long i = 0; i < list->getSize(); i++){
                                T &ls = list->get(i); 
                                for(unsigned long j = 0; j < this->size; j++){
                                    if(cr->element == ls){
                                        Ereaseable<T>::erease(cr->element);
                                        if(firstDeleted == nullptr){
                                            firstDeleted = cr;
                                        }
                                        len++;
                                    }else{
                                        if(firstDeleted != nullptr){
                                            this->detach_s(firstDeleted, cr->previous, len);
                                            firstDeleted = nullptr;
                                            len = 0;
                                            this->size -= len;
                                        }
                                    }
                                    cr = cr->next;
                                }      
                                if(firstDeleted != nullptr){
                                    this->detach_s(firstDeleted, cr, len);
                                    this->size -= len;
                                }                        
                            }

                        }
                        virtual void removeAllIf(_functional::Predicate<T> predicate) noexcept override{
                            Node* cr = this->head;
                            Node* &firstDeleted = nullptr;
                            unsigned long len = 0;
                            for(unsigned long i = 0; i < this->size; i++){
                                if(predicate.test(cr->element)){
                                    Ereaseable<T>::erease(cr->element);
                                    if(firstDeleted == nullptr){
                                        firstDeleted = cr;
                                    }
                                    len++;
                                }else{
                                    if(firstDeleted != nullptr){
                                        this->detach_s(firstDeleted, cr->previous, len);
                                        firstDeleted = nullptr;
                                        this->size -= len;
                                        len = 0;
                                    }
                                }
                                cr = cr->next;
                            }
                            if(firstDeleted != nullptr){
                                this->detach_s(firstDeleted, cr, len);
                                this->size -= len;
                            }  
                        }
                        virtual T set(unsigned long index, const T &t) override {}
                        virtual List<T>* subList(unsigned long start, unsigned long end) const override {return NULL;}
                        virtual List<T>* subList(unsigned long start) const override {return NULL;}
                        virtual void forEach(_functional::Consumer<T> consumer) override {
                            Node* cr = this->head;
                            for(unsigned long i = 0; i < this->size; i++){
                                consumer.test(cr->element);
                                cr = cr->next;
                            }
                        }
                        virtual T* toArray() const noexcept override{return NULL;}

                        virtual void compress() noexcept override{
                            Node* cr = this->head;
                            Node* &firstNull = nullptr;
                            unsigned long len = 0;
                            for(unsigned long i = 0; i < this->size; i++){
                                if(Nullable<T>::isNull(cr->element)){
                                    if(firstNull == nullptr)
                                        firstNull = cr;
                                    len++;
                                }else{
                                    if(firstNull != nullptr){
                                        this->detach_s(firstNull, cr->previous, len);
                                        firstNull = nullptr;
                                        this->size -= len;
                                        len = 0;
                                    }
                                }
                                cr = cr->next;
                            }
                            if(firstNull != nullptr){
                                this->detach_s(firstNull, cr, len);
                                this->size -= len;
                            }     
                        }

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
}

#endif