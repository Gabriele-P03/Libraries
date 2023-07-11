/**
 * @file 
 * 
 * This class file can be assimilated as an interface.
 * There are some function declarations which will be used by all collection-structure-type, such as 
 * ArrayList, LinkedList, Stack and Queue.
 * 
 * Since JPL provides Exception module, and, as an elephant in the room, it cannot be used into
 * pre-existing structure provided by std, this sub-module provides the same kinda of structures but
 * with the auxiliary use of Exception module   
 * 
 * @date 2023-05-28
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef COLLECTION_STRUCTURE_JPL
#define COLLECTION_STRUCTURE_JPL

namespace jpl{

    namespace _utils{

        namespace _structure{
            
            template <typename T>
            class Collection{

                protected:
                    
                    /**
                     * @brief It stores the current amount of items into the structure
                     */
                    unsigned long size;

                    
                    unsigned long max;

                pubic:

                    /**
                     * @brief Insert t into the structure. The position where t is pushed depends
                     * by the type of structure
                     * 
                     * @param t 
                     * @return t in case of success otherwise nullptr
                     */
                    virtual inline T add(T t);
                    /**
                     * @brief Insert into the structure all items contained into list
                     * 
                     * @param list 
                     */
                    virtual inline void addAll(List<T> *list);


                    /**
                     * @brief Check into the whole collection if t is present
                     * 
                     * @param t 
                     * @return if t is present
                     */
                    virtual bool inline contains(T t);
                    /**
                     * @brief Check if all collection's items are stored into this one
                     * 
                     * @param collection to compare with this one
                     * @return if all collection's items are present
                     */
                    virtual bool inline containsAll(Collection<T> collection);


                    /**
                     * @brief remove t from this collection
                     * 
                     * @param t item to remove
                     * @throw NotFoundException if t has not been found into this collection
                     */
                    virtual void inline remove(T t);
                    /**
                     * @brief remove all collection's items from this collection
                     * 
                     * @param list collection of items to remove
                     * @throw NotFoundException at the first item not found
                     */
                    virtual void inline removeAll(Collection<T> list);

                    /**
                     * @return if the structure is empty
                     */
                    virtual bool inline isEmpty(){return this->size == 0;}

                    /**
                     * @return the current amount of items contained into this collection
                     */
                    virtual unsigned long inline size(){return this->size;};

                    /**
                     * @brief In order to offers you the most available compatibility to any others
                     * type of structures (even not JPL's), a collection can be copied into an array
                     * 
                     * @return T* (get its size by size())
                     */
                    virtual T* toArray();

            };
        } 
    }
}

#endif
