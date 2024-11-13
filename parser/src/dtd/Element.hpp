/**
 * @file
 * 
 * DTD Element representation.
 * 
 * Since a DTD does not respect any order about elements declaration, at first they are stored into a single LinkedList in parsing-time; once 
 * it is over, the root one will be copy-constructed and the buffer LinkedList will be destroyed. Check DTDUtils.cpp
 * 
 * 
 * @author Gabriele-P03 
 */

#ifndef ELEMENT_DTD_JPL
#define ELEMENT_DTD_JPL

#include "Attribute.hpp"
#include "ElementList.hpp"

namespace jpl{
    namespace _parser{

        namespace _xml{
            extern void validateName(const std::string &name);
        }

        namespace _dtd{
            
            class Element{

                private:
                    ElementList* elementList;
                    jpl::_utils::_collections::_list::LinkedList<Attribute*>* attributes;
                    const std::string name;
                    TYPE_LIST type_list;
                
                public:

                    Element(const std::string &name) : Element(name, new jpl::_utils::_collections::_list::LinkedList<Attribute*>(), ANYTHING){}

                    Element(const std::string& name, jpl::_utils::_collections::_list::LinkedList<Attribute*>* attributes, const TYPE_LIST& type_list) 
                        : Element(name, attributes, type_list, new ElementList()){}
                    Element(const std::string& name, jpl::_utils::_collections::_list::LinkedList<Attribute*>* attributes, const TYPE_LIST& type_list, ElementList* elementList) : name(name){
                        _xml::validateName(this->name);
                        this->attributes = attributes;
                        this->type_list = type_list;
                        this->elementList = elementList;
                    }

                    const std::string &getName() const noexcept {return this->name;}
                    const TYPE_LIST getTypeList() const noexcept{return this->type_list;}
                    void setTypeList(const TYPE_LIST& type_list){
                        this->type_list = type_list;
                    }

                    void addAttribute(Attribute* attribute){
                        this->attributes->add(attribute);
                    }

                    ElementList* &getElementList() noexcept{return this->elementList;}

                    ~Element(){
                        if(this->attributes != nullptr){
                            delete this->attributes;
                        }
                        if(this->elementList != nullptr){
                            delete this->elementList;
                        }
                    }

            };
        }
    }
}

#endif