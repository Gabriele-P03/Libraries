/**
 * @file 
 * 
 * This is an interface.
 * 
 * Since JPL provides Exception module, and, as an elephant in the room, it cannot be used into
 * pre-existing structure provided by std, this sub-module provides the same kinda of structures but
 * with the auxiliary use of Exception module  
 * 
 * All data-structures deal with their elemets through std::unique_ptr in order to let it to destroy
 * element once no more unique_ptr own it. When you retrieve an element from a collection, it is not
 * detached from the relative unique_ptr, but a pointer to the element is given to you
 *  
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef COLLECTIONI_JPL
#define COLLECTIONI_JPL

#include "Iterable.hpp"
#include "Ereaseable.hpp"
#include "Printable.hpp"
#include "../functional/predicate/Predicate.hpp"

#include <concepts>

namespace jpl{

    namespace _utils{

        namespace _collections{
            
            template <typename T>
            class Collection : public Iterable<T>, public Ereaseable<T>{

                protected:



                    /**
                     * @brief It stores the max amount of items which can be contained into the collection
                     * 
                     * A collection is by itselves increaseable, a data-structure could set it as final in its own scope.
                    */
                    unsigned long max;
                    
                    /**
                     * @brief It stores the current amount of items into the structure
                     */
                    unsigned long size;

                    /**
                     * @brief if null elements are allowd to be inserted into the collection
                    */
                    bool nullableElements;

                    Collection(unsigned long max, unsigned long size, bool nullableElements){
                        this->max = max;
                        this->size = size;
                        this->nullableElements = nullableElements;
                    }

                public:

                    /**
                     * @brief Insert t into the structure. The position where t is pushed depends
                     * by the type of structure
                     * 
                     * @param t 
                     * @throw NullPointerException if list does not permit null elements and t it is
                     */
                    virtual void add(const T &t) = 0;


                    /**
                     * @brief Check into the whole collection if t is present
                     * 
                     * @param t 
                     * @return if t is present
                     */
                    virtual bool contains(const T &t) const noexcept = 0;


                    /**
                     * @brief Remove all elements from the collection
                    */
                    virtual void clear() noexcept = 0;



                    /**
                     * @return if the structure is empty
                     */
                    virtual bool isEmpty() noexcept {return this->size == 0;}

                    /**
                     * @return the max amount of items which can contained into the collection
                     */
                    virtual const unsigned long getMax() const noexcept {return this->max;}
                    /**
                     * @return the current amount of items which are contained into the collection 
                    */
                   virtual const unsigned long getSize() const noexcept {return this->size;}
                    /**
                     * @return if the collection allows null elements
                    */
                   virtual bool allowNull() noexcept {return this->nullableElements;}

                    /**
                     * @brief In order to offers you the most available compatibility to any others
                     * type of structures (even not JPL's), any collection can be copied into an array
                     * 
                     * Every array returned by a collection will be a copy of the original one: no changes
                     * performed on the returned array will be done even on the collection.
                     * The array returned will be as length as size field.
                     * 
                     * @return T* (get its size by length())
                     */
                    virtual T* toArray() const noexcept = 0;
            };
        } 
    }
}

#endif
