#include "JSONField.hpp"

template<typename T>
jpl::_parser::_json::JSONField<T>::JSONField(std::string name, unsigned long tabs, T value){
    this->name = name;
    this->tabs = tabs;
    this->value = value;
}
template<typename T>
jpl::_parser::_json::JSONField<T>::JSONField(std::string name, T value) : jpl::_parser::_json::JSONField<T>(name, 0, value) {}
template<typename T>
jpl::_parser::_json::JSONField<T>::JSONField(std::string name){
    this->name = name;
    this->tabs = 0;
}
template<typename T>
jpl::_parser::_json::JSONField<T>::JSONField() : JSONField(""){}

template <typename T>
T jpl::_parser::_json::JSONField<T>::getValue() const noexcept {return this->value;}
template <typename T>
std::string jpl::_parser::_json::JSONField<T>::getName() const noexcept {return this->name;}
template <typename T>
unsigned long jpl::_parser::_json::JSONField<T>::getTabsCount() const noexcept {return this->tabs;}
template <typename T>
void jpl::_parser::_json::JSONField<T>::setValue(T value) noexcept {this->value = value;}
template <typename T>
void jpl::_parser::_json::JSONField<T>::setName(std::string name) noexcept{ this->name = name; }
template <typename T>
void jpl::_parser::_json::JSONField<T>::setTabsCount(unsigned long tabs) noexcept{ this->tabs = tabs; } 

template class jpl::_parser::_json::JSONField<int>;
template class jpl::_parser::_json::JSONField<unsigned int>;

template class jpl::_parser::_json::JSONField<long>;
template class jpl::_parser::_json::JSONField<unsigned long>;

template class jpl::_parser::_json::JSONField<float>;
template class jpl::_parser::_json::JSONField<double>;
template class jpl::_parser::_json::JSONField<bool>;
template class jpl::_parser::_json::JSONField<std::tm>;
template class jpl::_parser::_json::JSONField<std::string>;