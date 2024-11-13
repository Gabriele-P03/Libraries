#include "ElementList.hpp"

void jpl::_parser::_dtd::ElementList::addElement_OCC(jpl::_parser::_dtd::Element_OCC* element_occ){
    const std::string &newName = jpl::_parser::_dtd::getNameByElementPtr(element_occ->element);
    for(size_t i = 0; i < this->elements->getSize(); i++){
        jpl::_parser::_dtd::Element_OCC* cr = this->elements->get(i);
        const std::string &crName = jpl::_parser::_dtd::getNameByElementPtr(cr->element);
        if(crName.compare(newName) == 0 || cr == element_occ){
            throw jpl::_exception::RuntimeException("The element list already contains the " + newName + " element");
        }
    }
    this->elements->add(element_occ);
}

void jpl::_parser::_dtd::ElementList::addElementList(jpl::_parser::_dtd::ElementList* elementList){
    for(size_t i = 0; i < this->elementLists->getSize(); i++){
        jpl::_parser::_dtd::ElementList* cr = this->elementLists->get(i);
        if(cr == elementList){
            throw jpl::_parser::_dtd::_exception::DTDDuplicateException("The element list already contains this sub element list");
        }
    }
    this->elementLists->add(elementList);
}