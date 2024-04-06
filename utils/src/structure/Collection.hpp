/**
 * @file 
 * 
 * An knowledgment of DSA theory is required, since these documentation are not intendeed to explain it...
 * 
 * This is the top-level of all JPL's data-structures hierarchy. 
 * It stores some properties which are common to each of them and which describe their behaviour, such as null 
 * elements permission, duplicates, resizeable and so on.
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef COLLECTIONI_JPL
#define COLLECTIONI_JPL

#include "functional/Iterable.hpp"
#include "functional/Printable.hpp"
#include "functional/Copyable.hpp"
#include "functional/Nullable.hpp"
#include "functional/Ereaseable.hpp"
#include "functional/Pointerable.hpp"
#include "../functional/predicate/Predicate.hpp"

#include <concepts>

namespace jpl{

    namespace _utils{

        namespace _collections{
            
            template <typename T>
            class Collection : public Iterable<T>{

                protected:



                    /**
                     * @brief It stores the max amount of items which can be contained into the collection
                     * 
                     * A collection is by itselves increaseable, a data-structure could set it as final in its own scope.
                    */
                    unsigned long max = 0;
                    
                    /**
                     * @brief It stores the current amount of items into the structure
                     */
                    unsigned long size = 0;

                    /**
                     * @brief if null elements are allowd to be inserted into the collection
                    */
                    bool nullableElements;

                    /**
                     * @brief if duplicate elements are allowed
                    */
                   bool duplicateElements;

                   /**
                    * @brief if the collection is resizeable
                   */
                   bool resizeable;

                    /**
                     * @brief if T is a pointer
                    */
                   bool pointer;

                    Collection(bool nullableElements, bool duplicateElements, bool resizeable){
                        this->duplicateElements = duplicateElements;
                        this->nullableElements = nullableElements;
                        this->resizeable = resizeable;
                        this->pointer = Pointerable<T>::isPointer();
                    }

                public:

                    /**
                     * @brief Insert t into the structure. The position t is added at depends on type of structure
                     * 
                     * @param t 
                     * @throw NullPointerException if list does not permit null elements and t is nullptr
                     */
                    virtual void add(T t) = 0;


                    /**
                     * @param t 
                     * @return Check if the collection contains t
                     */
                    virtual bool contains(T t) const noexcept = 0;


                    /**
                     * @brief Remove all elements from the collection
                    */
                    virtual void clear() noexcept = 0;


                    /**
                     * @return if the structure is empty
                     */
                    bool isEmpty() noexcept {return this->size == 0;}


                    /**
                     * @return the max amount of items which can contained into the collection
                     */
                    const unsigned long getMax() const noexcept {return this->max;}
                    /**
                     * @return the current amount of items which are contained into the collection 
                    */
                    const unsigned long getSize() const noexcept {return this->size;}
                    /**
                     * @return if the collection allows null elements
                    */
                    const bool allowNull() const noexcept {return this->nullableElements;}
                    /**
                     * @return if the collection allows duplicate elements
                    */
                    const bool allowDuplicate() const noexcept {return this->duplicateElements;}
                    /**
                     * @return if the collection is resizeable
                    */
                    const bool allowResize() const noexcept {return this->resizeable;}
                    /**
                     * @return if T is a pointer
                    */
                    const bool isPointer() const noexcept {return this->pointer;}

                    /**
                     * @brief In order to offers you the most available compatibility to any others
                     * type of structures (even not JPL's), any collection can be copied into an array
                     * 
                     * Each array returned by a collection will be a mirror-copy of this one, therefore
                     * if the template type is a pointer, in the array you will have right them (a new
                     * allocation of them will not be done)
                     * 
                     * @return T* (get its size by getSize())
                     */
                    virtual T* toArray() const noexcept = 0;
            };
        } 
    }
}

#endif
