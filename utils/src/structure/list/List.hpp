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

namespace jpl{

    namespace _utils{

        namespace _collections{
            
            template <typename T>
            class List : protected Collection<T>{

                private:
                    bool nullableElements;

                protected:

                    /**
                     * Create a new empty list
                     * 
                     * @param size size of the list
                     * @param nullableElements if this list allow null elements
                    */
                    template <typename T> List<T>(unsigned long size, bool nullableElements){
                        this->size = size;
                        this->nullableElements = nullableElements;
                    }

                    template <typename T> List<T>(unsigned long size) : List<T> (size, true){}
                    template <typename T> List<T>() : List<T> (0, true){}

                public:

                    /**
                     * Insert the given t at index
                     * 
                     * @param index index
                     * @param t new element
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual void add(unsigned long index, T* t);
                    /**
                     * Insert the whole given list at index
                     * 
                     * @param index
                     * @param collection
                    */
                    virtual void addAll(unsigned long index, Collection<T> collection);
            

                    /**
                     * @return the element at the given index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than size()-1 or less than 0
                    */
                    virtual T* get(unsigned long index);


                    /**
                     * @return the index of the first occurrence of t. If t is not found into the list, it returns -1
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual unsigned long firstOccurrence(T t);
                    /**
                     * @return the index of the last occurrence of t. If t is not found into the list, it returns -1
                     * 
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual unsigned long lastOccurrence(T t);

                    
                    /**
                     * @brief remove the element at the given index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than size()-1 or less than 0
                    */
                    virtual void remove(unsigned long index);


                    /**
                     * Set t at the given index (which was already occuped)
                     * 
                     * @return the previous element which was at index
                     * 
                     * @throw IndexOutOfBounds if index is graeter than size()-1 or less than 0
                     * @throw NullPointerException if list does not permit null elements and t it is
                    */
                    virtual T set(unsigned long index, T t);

                    /**
                     * @return a sub list of the current one
                     * 
                     * @throw IndexOutOfBounds if start is graeter than size()-1 or less than 0
                     * @throw IndexOutOfBounds if end is graeter than size()-1 or less than 0
                    */
                    virtual List<T> subList(unsigned long start, unsigned long end);
            };
        }
    }
}

#endif