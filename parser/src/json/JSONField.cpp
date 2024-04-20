#include "JSONField.hpp"

template <typename T>
jpl::_parser::_json::JSONField<T>::JSONField(std::string name, unsigned long tabs, T value){
    this->name = name;
    this->tabs = tabs;
    this->value = value;
}