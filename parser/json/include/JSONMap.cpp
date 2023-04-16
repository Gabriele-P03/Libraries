#include "JSONMap.hpp"

JSON::JSONMap::JSONMap(std::string mapAsString){
    this->key = mapAsString.substr(0, mapAsString.find(':'));
    this->value = mapAsString.substr(this->key.size()+1);
}

JSON::JSONMap::JSONMap(std::string key, std::string value){
    this->key = key;
    this->value = value;
}

std::string* JSON::JSONMap::to_string(){
    return new std::string( "\"" + this->key + "\":\"" + this->value + "\"");
}