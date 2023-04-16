#include "JSONArray.hpp"

JSON::JSONArray::JSONArray(std::string arrayAsString) : 
JSON::JSONArray::JSONArray(arrayAsString, 0){}

JSON::JSONArray::JSONArray(std::string arrayAsString, unsigned int offset){

    std::string buffer = "";

    unsigned int i;

    for(i = offset; i < arrayAsString.size(); i++){

        char current = arrayAsString.at(i);

        if(current == '{'){
            JSON::JSONObject obj = JSON::JSONObject(arrayAsString, i+1);
            obj.name = buffer;
            this->objects.push_back(obj);
            i += obj.getSize();
        }else if(current == '['){
            JSON::JSONArray array = JSON::JSONArray(arrayAsString, i+1);
            array.name = buffer;
            this->arrays.push_back(array);
            i += array.getSize();
        }else if(current == ','){
            if(!buffer.empty())
                this->values.push_back(buffer);
            else
                continue;
        }else if(current == ']'){
            i++;
            break;
        }else{
            buffer += current;
            continue;
        }

        buffer = "";
    }

    if(!buffer.empty()){
        this->values.push_back(buffer);
    }
    
    this->size = i - offset;
}

unsigned int JSON::JSONArray::getSize(){
    return this->size;
}


std::string* JSON::JSONArray::to_string(){
    
    std::string buffer;

    if(!this->name.empty()){
        buffer += "\"" + this->name + "\":";
    }

    buffer += "[";

    for(int i = 0; i < this->objects.size(); i++){
        buffer += *this->objects.at(i).to_string();
        if(i < this->objects.size()-1 || this->arrays.size() > 0 || this->values.size() > 0){
            buffer += ",";
        }
    }
    for(int i = 0; i < this->arrays.size(); i++){
        buffer += *this->arrays.at(i).to_string();
        if(i < this->arrays.size()-1 || this->values.size() > 0){
            buffer += ",";
        }
    }
    for(int i = 0; i < this->values.size(); i++){
        buffer += this->values.at(i);
        if(i < this->values.size()-1){
            buffer += ",";
        }
    }

    buffer += "]";

    return new std::string(buffer);
}