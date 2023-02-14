#include "JSONObject.hpp"

JSON::JSONObject::JSONObject(std::string jsonAsString) :
JSON::JSONObject::JSONObject(jsonAsString, 0){}

JSON::JSONObject::JSONObject(std::string jsonAsString, unsigned int offset){

    std::string buffer = "";

    unsigned int i;

    for(i = offset; i < jsonAsString.size(); i++){

        char current = jsonAsString.at(i);

        if(current == ':'){

            if(i < jsonAsString.size() - 1){
                char next = jsonAsString.at(i+1);

                if(next == '{'){
                    JSON::JSONObject obj = JSON::JSONObject(jsonAsString, i+2);
                    obj.name = buffer;
                    this->objects.push_back(obj);
                    i += obj.size + 1;
                }else if(next == '['){
                    JSON::JSONArray array = JSON::JSONArray(jsonAsString, i+2);
                    array.name = buffer;
                    this->arrays.push_back(array);
                    i += array.getSize() + 1;
                }else{
                    //Means that is coming a map
                    //JSONMap constructor parse ':' by itself
                    buffer += current;
                    continue;
                }
            }
        }else if(current == ','){
            if(!buffer.empty())
                this->maps.push_back(JSON::JSONMap(buffer));
            else
                continue;
        }else if(current == '}'){
            i++;
            break;  
        }else{
            buffer += current;
            continue;
        }

        buffer = "";
    }

    if(!buffer.empty()){
        this->maps.push_back(JSON::JSONMap(buffer));
    }
    
    this->size = i - offset;
}

unsigned int JSON::JSONObject::getSize(){
    return this->size;
}

std::string* JSON::JSONObject::to_string(){

    std::string buffer;

    if(!this->name.empty()){
        buffer += "\"" + this->name + "\":";
    }

    buffer += "{";

    for(int i = 0; i < this->objects.size(); i++){
        buffer += *this->objects.at(i).to_string();
        if(i < this->objects.size()-1 || this->arrays.size() > 0 || this->maps.size() > 0){
            buffer += ",";
        }
    }
    for(int i = 0; i < this->arrays.size(); i++){
        buffer += *this->arrays.at(i).to_string();
        if(i < this->arrays.size()-1 || this->maps.size() > 0){
            buffer += ",";
        }
    }
    for(int i = 0; i < this->maps.size(); i++){
        buffer += *this->maps.at(i).to_string();
        if(i < this->maps.size()-1){
            buffer += ",";
        }
    }

    buffer += "}";

    return new std::string(buffer);
}

JSON::JSONObject* JSON::JSONObject::getJSONObjectByName(std::string name){

    for(int i = 0; i < this->objects.size(); i++){
        if(this->objects[i].name == name)
            return &this->objects[i];
    }

    return nullptr;
}

JSON::JSONArray* JSON::JSONObject::getJSONArrayByName(std::string name){

    for(int i = 0; i < this->arrays.size(); i++){
        if(this->arrays[i].name == name)
            return &this->arrays[i];
    }

    return nullptr;
}

JSON::JSONMap* JSON::JSONObject::getJSONMapByKey(std::string key){

    for(int i = 0; i < this->maps.size(); i++){
        if(this->maps[i].key == key)
            return &this->maps[i];
    }

    return nullptr;
}