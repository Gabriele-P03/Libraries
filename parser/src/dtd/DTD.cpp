#include "DTD.hpp"

jpl::_parser::_dtd::DTD::DTD(
    const jpl::_parser::_dtd::Element* root,
    const jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*>* elements,
    const jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Entity*>* entities
) : root(root), elements(elements), entities(entities){

    if(this->root == nullptr){
        throw jpl::_exception::IllegalArgumentException("Root element is nullptr");
    }
    if(this->elements == nullptr){
        throw jpl::_exception::IllegalArgumentException("Elements list is nullptr");
    }
    if(!this->elements->contains(const_cast<jpl::_parser::_dtd::Element*>(this->root))){
        throw jpl::_exception::RuntimeException("It seems like root element is not contained into elements list");
    }
    if(this->entities == nullptr){
        throw jpl::_exception::IllegalArgumentException("Entities list is nullptr");
    }
}

const jpl::_parser::_dtd::Element* jpl::_parser::_dtd::DTD::getElementByName(const std::string &name) const{
    for(size_t i = 0; i < this->elements->getSize(); i++){
        jpl::_parser::_dtd::Element* cr = this->elements->get(i);
        if(cr->getName().compare(name) == 0){
            return const_cast<const jpl::_parser::_dtd::Element*>(cr);
        }
    }
    throw jpl::_exception::NotFoundException("There's no element called as " + name);
}

const jpl::_parser::_dtd::Entity* jpl::_parser::_dtd::DTD::getEntityByName(const std::string &name) const{
    for(size_t i = 0; i < this->entities->getSize(); i++){
        jpl::_parser::_dtd::Entity* cr = this->entities->get(i);
        if(cr->getName().compare(name) == 0){
            return const_cast<const jpl::_parser::_dtd::Entity*>(cr);
        }
    }
    throw jpl::_exception::NotFoundException("There's no entity called as " + name);
}