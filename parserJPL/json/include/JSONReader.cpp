#include "JSONReader.hpp"

std::string* JSON::read(std::string path){

    std::fstream* file = new std::fstream();
    file->open(path, std::ios_base::in);

    return JSON::read(file);
}

std::string* JSON::read(std::fstream* &file){

    if(file != nullptr){
        //Store the length of the file in order to create the right sized buffer
        file->seekg(0, file->end);
        unsigned int length = file->tellg();
        file->seekg(0, file->beg);

        char* buffer = new char[length];

        //fstram#read return file without errors once it has been read successfully
        if(file->read(buffer, length)){
            buffer[length] = '\0';

            std::string* buf = new std::string(buffer, length);
            boost::replace_all(*buf, "", "");
            boost::replace_all(*buf, " ", "");
            boost::replace_all(*buf, "\"", "");
            boost::replace_all(*buf, "\n", "");

            return buf;
        }else{
            jpl::print("Error during file reading. I've read only: " + std::string(buffer));
            return nullptr;
        }

        delete buffer;
    }else{
        return nullptr;
    }
}

std::variant<JSON::JSONObject*, JSON::JSONArray*, JSON::READ_ERROR> JSON::parse(std::string jsonAsString){

    if(jsonAsString.length() > 0){

        boost::replace_all(jsonAsString, "", "");
        boost::replace_all(jsonAsString, " ", "");
        boost::replace_all(jsonAsString, "\"", "");
        boost::replace_all(jsonAsString, "\n", "");

        char first = jsonAsString.at(0);

        if(first == '['){

            return new JSON::JSONArray(jsonAsString.substr(1, jsonAsString.size()-2));
        }else if(first == '{'){

            return new JSON::JSONObject(jsonAsString.substr(1, jsonAsString.size()-2));
        }else{
            return JSON::STRANGE_CHAR_IN_STRING;
        }
    }else{
        return JSON::EMPTY_STRING;
    }
}


JSON::JSONObject* JSON::getJSONObject(std::string jsonAsString){

    try{
        return std::get<JSON::JSONObject*>(JSON::parse(jsonAsString));
    }catch(std::bad_variant_access const& ex){
        jpl::print(ex.what());
    }

    return nullptr;
}

JSON::JSONArray* JSON::getJSONArray(std::string jsonAsString){

    try{
        return std::get<JSON::JSONArray*>(JSON::parse(jsonAsString));
    }catch(std::bad_variant_access const& ex){
        jpl::print(ex.what()) ;
    }

    return nullptr;
}