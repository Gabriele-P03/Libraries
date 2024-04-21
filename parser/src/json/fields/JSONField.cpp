#include "JSONField.hpp"

jpl::_parser::_json::JSONField::JSONField(std::string name, unsigned long tabs, T value){
    this->name = name;
    this->tabs = tabs;
    this->value = value;
}
jpl::_parser::_json::JSONField::JSONField(std::string name, T value){
    this->name = name;
    this->value = value;
}
jpl::_parser::_json::JSONField::JSONField(std::string name){
    this->name = name;
}
jpl::_parser::_json::JSONField::JSONField() : JSONField(""){}

virtual T jpl::_parser::_json::JSONField::getValue() const noexcept {return this->value;}
virtual std::string jpl::_parser::_json::JSONField::getName() const noexcept {return this->name;}
virtual unsigned long jpl::_parser::_json::JSONField::getTabsCount() const noexcept {return this->tabs;}

virtual void jpl::_parser::_json::JSONField::setValue(T value) noexcept {this->value = value;}
virtual void jpl::_parser::_json::JSONField::setName(std::string name) noexcept{ this->name = name; }
virtual void jpl::_parser::_json::JSONField::setTabsCount(unsigned long tabs) noexcept{ this->tabs = tabs; } 