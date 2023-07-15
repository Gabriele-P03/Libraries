/**
 * @file 
 * 
 * This is an interface.
 * 
 * Since JPL provides Exception module, and, as an elephant in the room, it cannot be used into
 * pre-existing structure provided by std, this sub-module provides the same kinda of structures but
 * with the auxiliary use of Exception module   
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef COLLECTIONI_JPL
#define COLLECTIONI_JPL

/*

    IMMETTERE IN INCLUDE L'ATTUALE VERSIONE DELLA JPL

*/

#include "Iterable.hpp"
#include "../functional/predicate/Predicate.hpp"

namespace jpl{

    namespace _utils{

        namespace _collections{
            
            template <typename T>
            class Collection : public Iterable<T>{

                protected:
                    
                    /**
                     * @brief It stores the current amount of items into the structure
                     */
                    unsigned long size;


                    void assertIndex(unsigned long index){
                        if(index >= this->size){

                        }
                    }

                public:

                    /**
                     * @brief Insert t into the structure. The position where t is pushed depends
                     * by the type of structure
                     * 
                     * @param t 
                     * 
                     */
                    virtual bool add(T* t) = 0;
                    /**
                     * @brief Insert into the structure all items contained into list
                     * 
                     * @param list 
                     */
                    virtual bool addAll(Collection<T> *list) = 0;


                    /**
                     * @brief Check into the whole collection if t is present
                     * 
                     * @param t 
                     * @return if t is present
                     */
                    virtual bool contains(T* t) = 0;
                    /**
                     * @brief Check if all collection's items are stored into this one
                     * 
                     * @param collection to compare with this one
                     * @return if all collection's items are present
                     */
                    virtual bool containsAll(Collection<T*> collection) = 0;


                    /**
                     * @brief remove t from this collection
                     * 
                     * @param t item to remove
                     * @throw NotFoundException if t has not been found into this collection
                     */
                    virtual void remove(T t) = 0;
                    /**
                     * @brief remove all collection's items from this collection
                     * 
                     * @param list collection of items to remove
                     * @throw NotFoundException if at least one item into list has not been found
                     */
                    virtual void removeAll(Collection<T*> list) = 0;
                    /**
                     * @brief Remove all elements which respect the given predicate
                    */
                    virtual void removeAllIf(_functional::Predicate<T*> predicate) = 0;
                    /**
                     * @brief Remove all elements from the collection
                    */
                    virtual void clear() = 0;



                    /**
                     * @return if the structure is empty
                     */
                    virtual bool isEmpty(){return this->size == 0;}

                    /**
                     * @return the current amount of items contained into this collection
                     */
                    virtual unsigned long length(){return this->size;}

                    /**
                     * @brief In order to offers you the most available compatibility to any others
                     * type of structures (even not JPL's), a collection can be copied into an array
                     * 
                     * @return T* (get its size by length())
                     */
                    virtual T* toArray() = 0;

            };
        } 
    }
}

#endif
