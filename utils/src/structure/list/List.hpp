/**
 * @file
 * 
 * This is an interface
 * 
 * A list is like a Set, but it does allow null and dulicate elements both.
 * 
 * A list is an indexed super-type collection, it means that you can insert elements via an index 
 * 
 * @date 2023-07-12
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
*/

#ifndef LISTI_JPL
#define LISTI_JPL

#include "../Collection.hpp"
#include <jpl/exception/runtime/IndexOutOfBoundsException.hpp>
#include <jpl/exception/runtime/NotFoundException.hpp>

namespace jpl{

    namespace _utils{

        namespace _collections{
            
            template <typename T>
            class List : public Collection<T>{
                    
                protected:

                    /**
                     * Create a new empty list
                     * 
                     * @param size size of the list
                     * @param nullableElements if this list allow null elements
                    */
                    List(unsigned long size, bool nullableElements) : Collection<T>(size, size, nullableElements){}
                    List(unsigned long size) : List<T> (size, true){}
                    List() : List<T> (0, true){}

                public:

                    /**
                     * Insert the given t at index
                     * 
                     * @param index index
                     * @param t new element
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual void add(unsigned long index, T t) = 0;
                    /**
                     * Insert the whole given list at index
                     * 
                     * @param index
                     * @param collection
                    */
                    virtual void addAll(unsigned long index, const List<T>* &list) = 0;
                    /**
                    * @brief Insert into the structure all items contained into list at the end
                    * if the array list
                    * 
                    * @param list 
                    */
                    virtual void addAll(const List<T>* &list) = 0;          

                    /**
                     * @return the element at the given index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than length()-1 or less than 0
                    */
                    virtual T* get(unsigned long index) const = 0;


                    /**
                     * @return the index of the first occurrence of t. 
                     * If t is not found into the list, it returns max
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual unsigned long firstOccurrence(T* t) = 0;
                    /**
                     * @return the index of the last occurrence of t.
                     * If t is not found into the list, it returns max
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual unsigned long lastOccurrence(T* t) = 0;

                    
                    /**
                     * @brief remove the element at the given index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than length()-1 or less than 0
                    */
                    virtual void remove(unsigned long index) = 0;
                    /**
                     * @brief remove t from this collection
                     * 
                     * @param t item to remove
                     * @throw NotFoundException if t has not been found into this collection
                     */
                    virtual void remove(T* t) = 0;                    
                    /**
                     * @brief remove all collection's items from this collection
                     * 
                     * @param list collection of items to remove
                     * @throw NotFoundException if at least one item into list has not been found
                     */
                    virtual void removeAll(List<T>* list) = 0;
                    /**
                     * @brief Remove all elements which respect the given predicate
                    */
                    virtual void removeAllIf(_functional::Predicate<T>* predicate) noexcept = 0;

                    /**
                     * Set t at the given index (which was already occuped)
                     * 
                     * @return the previous element which was at index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than length()-1 or less than 0
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual T* set(unsigned long index, T t) = 0;

                    /**
                     * @return a sub list of the current one. If start is equals to end, am empty list is returned
                     * 
                     * @param start index of the first element to copy
                     * @param end index of the last element to copy (included) 
                     * 
                     * @throw IndexOutOfBounds if start is graeter or equals than max
                     * @throw IndexOutOfBounds if end is graeter or equals than max
                    */
                    virtual List<T>* subList(unsigned long start, unsigned long end) = 0;
            };
        }
    }
}

#endif