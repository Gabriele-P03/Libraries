/**
 * @file
 * 
 * A DTD instance is the result of DTD parsing; it contains the root-element instance with all its children and attributes
 * and the linked list which contains all of them (1).
 * 
 * The linked list is also used by getter-by-name method in order to avoid a depth searching.
 * 
 * This class also provides some static methods which can be used by XML in order to validate its content.
 * 
 * Due to (1), and even in order to prevent double free, DTD's destructor does not destroy root and elements both; it does it only for elements list.
 * By the way, even  
 * 
 * @author Gabriele-P03
 */
#ifndef DTD_JPL
#define DTD_JPL

#include "Element.hpp"
#include "Entity.hpp"

namespace jpl{
    namespace _parser{
        namespace _dtd{

            class DTD{
                
                private:
                    const Element* root;
                    const _utils::_collections::_list::LinkedList<Element*>* elements;
                    const _utils::_collections::_list::LinkedList<Entity*>* entities;
                
                public:
                    /**
                     * @param root
                     * @param elements
                     * @param entities
                     * 
                     * @throw IllegalArgumentException if root is nullptr
                     * @throw IllegalArgumentException if elements is nullptr
                     * @throw IllegalArgumentException if entities is nullptr
                     * @throw RuntimeException if root is not contained into elements
                     */
                    DTD(const Element* root, const _utils::_collections::_list::LinkedList<Element*>* elements, const _utils::_collections::_list::LinkedList<Entity*>* entities);

                    /**
                     * @return the root element
                     */
                    const Element* getRoot() const noexcept { return this->root; }

                    /**
                     * @param name
                     * @throw NotFoundException if there is no element called as name
                     * @return the element called as name
                     */
                    const Element* getElementByName(const std::string &name) const; 

                    /**
                     * @param name
                     * @throw NotFoundException if there is no entity called as name
                     * @return the entity called as name
                     */
                    const Entity* getEntityByName(const std::string &name) const;

                    ~DTD(){
                        delete this->elements;
                        //delete this->root; //it is not required since it is already deleted by the previous istruction
                    }

            };
        }
    }
}

#endif