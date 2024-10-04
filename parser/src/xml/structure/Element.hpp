/**
 * 
 * @file
 * 
 * THe rappresentation of an XML element
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

                    Element(std::string name);
                    Element(
                        std::string name,
                        std::string text,
                        unsigned short tab,
                        _utils::_collections::_list::LinkedList<Element*> elements,
                        _utils::_collections::_list::LinkedList<Attribute*> attributes);

                    Element* getElement(std::string name) const;
                    bool hasElement(std::string name) const noexcept;
                    void addElement(Element* element);
                    void removeElement(std::string name);
                    void removeElement(Element* element);

                    Attribute* getAttribute(std::string name) const;
                    bool hasAttribute(std::string name) const noexcept;
                    void addAttribute(Attribute* attribute);
                    void removeAttribute(std::string name);
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

                    virtual std::string toString() const noexcept;

                    ~Element();
            };

        }
    }
}



#endif