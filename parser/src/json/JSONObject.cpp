#include "JSONObject.hpp"

jpl::_parser::_json::JSONObject::JSONObject(std::string name, unsigned long tabs){
    this->name = name;
    this->tabs = tabs;
} 
jpl::_parser::_json::JSONObject::JSONObject(std::string name) : jpl::_parser::_json::JSONObject(name, 0){} 
jpl::_parser::_json::JSONObject::JSONObject() : jpl::_parser::_json::JSONObject(""){}

jpl::_parser::_json::JSONObject::~JSONObject(){
    this->fields.clear();
    this->jsonArray.clear();
    this->jsonObjects.clear();
}