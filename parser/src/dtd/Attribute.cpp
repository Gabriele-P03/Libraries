#include "Attribute.hpp"

jpl::_parser::_dtd::Attribute::Attribute(const std::string &name, const ATTR_TYPE& attr_type, const ATTR_VALUE& attr_value,
    const std::string& value, const _utils::_collections::_list::LinkedList<std::string>* values) : name(name), attr_type(attr_type), attr_value(attr_value), value(value), values(values){

    if(this->name.empty()){
        throw _exception::IllegalArgumentException("An empty name is not valid for a DTD attribute");
    }
    if(this->attr_type == ATTR_TYPE::LIST_CHOICE){
        if(this->values == nullptr){
            throw _exception::IllegalArgumentException(this->name + " attribute cannot have nullptr values list");
        }
        if(this->values->isEmpty()){
            throw _exception::IllegalArgumentException(this->name + " attribute cannot have an empty values list");
        }
        if(!this->value.empty()){ //Check if value is contained into values list
            bool flag = false;
            for (size_t i = 0; i < this->values->getSize(); i++){
                const std::string cr = this->values->get(i);
                if(cr.compare(this->value)){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                throw _exception::RuntimeException(this->name + " attribute's values list does not contain " + this->value + " value");
            }
        }
    }
    if(this->attr_value == ATTR_VALUE::FIXED){
        if(this->value.empty()){
            throw _exception::IllegalArgumentException(this->name + " attribute must contain a fixed value but it is empty");
        }
    }
}

jpl::_parser::_dtd::Attribute::Attribute(const jpl::_parser::_dtd::Attribute &attribute) : 
    name(attribute.getName()), 
    attr_type(attribute.attr_type), 
    attr_value(attr_value), 
    value(attribute.value), 
    values(attribute.values){
    
}

jpl::_parser::_dtd::Attribute::~Attribute(){
    if(this->values != nullptr){
        delete this->values;
    }
}