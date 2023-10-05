/**
 * @file
 * 
 * A list is an ordered set of elements (either primitive types or object, either value or pointer) which are stored
 * as DSA theory - depending on its feature
 * 
 * In this header file there are only pure virtual methods which are used by all JPL's List data-structure.
 * 
 * All list implementation - unlike Set - allow you to insert duplicate elements
 * Some list implementation do not let you insert nullptr o NULL, throwing a JPL's NullPointerException
 * 
 * 
 * Methods as either set() or add() do put stuff you give them into the list; therefore, if you have 
 * declared an ArrayList of pointers, no new object will be allocated...
 * 
 * Just like insertion methods, even occurrence-checking methods work like them; therefore, if you have 
 * declared an ArrayList of pointers, memory address will be compareted
 * 
 * About removeAll ones, even them will cause a deletion of pointer into both list; therefore, once you 
 * had called one of them, you should also call compress() function on the one passed as argument 
 * in order to remove nullptr and resize it.
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
#include <jpl/exception/runtime/NullPointerException.hpp>

namespace jpl{

    namespace _utils{

        namespace _collections{
            
            template <typename T>
            class List : public Collection<T>{
                    
                protected:

                    /**
                     * Create a new empty list
                     * 
                     * @param nullableElements if this list allow null elements
                     * @param duplicateElements if this list allow duplicate elements
                     * @param resizeable if this list can be resized
                    */
                    List(bool nullableElements, bool duplicateElements, bool resizeable) : Collection<T>(nullableElements, duplicateElements, resizeable){}
                    List() : List<T> (true, true, true){}
                    /**
                     * Create a new List from the given collection
                     * 
                     * @param collection 
                     * @throw NullPointer if collection is nullptr
                    */
                    List(List<T>* list) : List<T>(){
                        if(list == nullptr){
                            throw new _exception::NullPointerException("You cannot pass a nullptr as list");
                        }
                    }
                    
                public:

                    /**
                     * Insert the given t at index
                     * 
                     * @param index index
                     * @param t new element
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                     * @throw RuntimeException if an element is already present into index position
                    */
                    virtual void add(unsigned long index, const T &t) = 0;
                    /**
                     * Insert the whole given list at index
                     * 
                     * @param index
                     * @param list
                     * 
                     * @throw NullPointerException if list does not permit null elements
                     * @throw NullPointerException if collection is nullptr
                    */
                    virtual void addAll(unsigned long index, List<T>* list) = 0;
                    /**
                    * @brief Insert into the structure all items contained into list at the end
                    * if the array list
                    * 
                    * @param list 
                    *
                    * @throw NullPointerException if list does not permit null elements
                    * @throw NullPointerException if collection is nullptr
                    */
                    virtual void addAll(List<T>* list) = 0;          

                    /**
                     * @return the element at the given index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than size
                    */
                    virtual T &get(unsigned long index) const = 0;


                    /**
                     * @return the index of the first occurrence of t. 
                     * If t is not found into the list, it returns max 
                    */
                    virtual unsigned long firstOccurrence(T t) const noexcept = 0;
                    /**
                     * @return the index of the last occurrence of t.
                     * If t is not found into the list, it returns max
                    */
                    virtual unsigned long lastOccurrence(T t) const noexcept = 0;

                    
                    /**
                     * @brief remove the element at the given index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than length()-1 or less than 0
                    */
                    virtual void removeAt(unsigned long index) = 0;
                    /**
                     * @brief remove t from this collection
                     * 
                     * @param t item to remove
                     * @throw NotFoundException if t has not been found into this collection
                     */
                    virtual void remove(T t) = 0;                    
                    /**
                     * @brief remove all list's items from this collection
                     * 
                     * @param list list of items to remove
                     * @throw NotFoundException if at least one item into list has not been found
                     */
                    virtual void removeAll(List<T>* list) = 0;
                    /**
                     * @brief Remove all elements which respect the given predicate
                     * @param predicate
                    */
                    virtual void removeAllIf(_functional::Predicate<T> predicate) noexcept = 0;

                    /**
                     * Set t at the given index (which was already occuped)
                     * 
                     * @return the previous element which was at index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than length()-1 or less than 0
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual T set(unsigned long index, const T &t) = 0;

                    /**
                     * @param start index of the first element to copy
                     * @param end index of the last element to copy (included) 
                     * 
                     * @return a sub list of the current one. If start is equals to end, am empty list is returned
                     * 
                     * @throw IndexOutOfBounds if start is graeter or equals than max
                     * @throw IndexOutOfBounds if end is graeter or equals than max
                    */
                    virtual List<T>* subList(unsigned long start, unsigned long end) const = 0;
                    /**
                     * @brief The list is computed 'till the end of the target oneremove
                     * 
                     * @param start index of the first element to copy
                     * 
                     * @return a sub list of the current one. If start is equals to end, am empty list is returned
                     * 
                     * @throw IndexOutOfBounds if start is graeter or equals than max
                    */
                    virtual List<T>* subList(unsigned long start) const = 0;

                    /**
                     * This functions performs only whereas T is a pointer
                     * It removes nullptr items from the list and resize it
                    */
                    virtual void compress() noexcept = 0;

            };
        }
    }
}

#endif