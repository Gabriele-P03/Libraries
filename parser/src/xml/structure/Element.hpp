/**
 * 
 * @file
 * 
 * THe rappresentation of an XML element
 * It does respect XML syntax about element's name, attributes list and text 
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */

#ifndef XML_ELEMENT_JPL
#define XML_ELEMENT_JPL

#include "Attribute.hpp"
#include "../exception/XMLDuplicateException.hpp"
#include "../exception/XMLNotFoundException.hpp"
#include <jpl/utils/structure/list/LinkedList.hpp>

namespace jpl{
    
    namespace _parser{
        
        namespace _xml{

            extern void validateName(std::string name);

            class Element{

                protected:
                    _utils::_collections::_list::LinkedList<Element*> elements;
                    _utils::_collections::_list::LinkedList<Attribute*> attributes;
                    std::string name;
                    std::string text;
                    unsigned short tabs;
                
                public:

                    /**
                     * Instance a new XML element
                     * 
                     * @param name 
                     * 
                     * @throw XMLValidationException if name does not respect XML Syntax 
                     */
                    Element(std::string name);
                    /**
                     * Instance a new XML element
                     * 
                     * @param name 
                     * @param text 
                     * @param tab how many \t whill be printed at left of current element
                     * @param elements list of children elements
                     * @param attributes list of attributes
                     * 
                     * @throw XMLValidationException if name does not respect XML Syntax 
                     */
                    Element(
                        std::string name,
                        std::string text,
                        unsigned short tab,
                        _utils::_collections::_list::LinkedList<Element*> elements,
                        _utils::_collections::_list::LinkedList<Attribute*> attributes);

                    /**
                     * @param name 
                     * @throw XMLNotFoundException if the current element has no child called as name
                     * @return the element with the given name
                     */
                    Element* getElement(std::string name) const;
                    /**
                     * @param name
                     * @return if the current element has a child called as name
                     */
                    bool hasElement(std::string name) const noexcept;
                    /**
                     * Add given element as child one
                     * @param element
                     * @throw IllegalArgumentExcption if element is nullptr
                     */
                    void addElement(Element* element);
                    /**
                     * @param name
                     * @throw XMLNotFoundException if no child element called as name has been found
                     */
                    void removeElement(std::string name);
                    /**
                     * @param element
                     * @throw IllegalArgumentExcption if element is nullptr
                     * @throw XMLNotFoundException if element has not been found
                     */
                    void removeElement(Element* element);


                    /**
                     * @param name 
                     * @throw XMLNotFoundException if the current element has no attribute called as name
                     * @return the attribute with the given name
                     */
                    Attribute* getAttribute(std::string name) const;
                    /**
                     * @param name
                     * @return if the current element has an attribute called as name 
                     */
                    bool hasAttribute(std::string name) const noexcept;
                    /**
                     * Add given attribute
                     * @param attribute
                     * @throw IllegalArgumentExcption if attribute is nullptr
                     * @throw XMLDuplicateException if there is already an attribute called as the given one
                     */
                    void addAttribute(Attribute* attribute);
                    /**
                     * @param name
                     * @throw XMLNotFoundException if no attribute called as name has been found
                     */
                    void removeAttribute(std::string name);
                    /**
                     * @param attribute
                     * @throw IllegalArgumentExcption if attribute is nullptr
                     * @throw XMLNotFoundException if attribute has not been found
                     */
                    void removeAttribute(Attribute* attribute);

                    std::string getName() const noexcept {return this->name;}
                    void setName(std::string name) {
                        validateName(name);
                        this->name = name;    
                    }
                    void setText(std::string text) noexcept {this->text = text;}
                    std::string getText() const noexcept {return this->text;}

                    void setTabs(unsigned short tabs) noexcept{this->tabs = tabs;}
                    unsigned short getTabs() const noexcept{return this->tabs;}

                    /**
                     * @return the representation of the current element as XML Syntax requires
                     */
                    virtual std::string toString() const noexcept;

                    ~Element();
            };

        }
    }
}



#endif