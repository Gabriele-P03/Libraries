#include "JSONUtils.hpp"


void* jpl::_parser::_json::parseJSONString(std::string &buffer, bool parseName, size_t tabs){
    buffer = jpl::_utils::_string::trim(buffer);
    if(buffer.length() < 2)
        throw new jpl::_parser::_json::_exception::JSONParseException("Json String: \"" + buffer + "\" seems like that it does not have opening/closing bracket");
    char s = buffer.at(0);
    if(s == '{'){
        size_t eS = jpl::_utils::_string::getIndexGroupOver(buffer, std::regex("\\{"), std::regex("\\}"));
        char e = buffer.at(eS);
        std::string b = jpl::_utils::_string::trim( buffer.substr(1, eS) ); //it also remove opening and closing bracket 
        jpl::_parser::_json::stct(buffer, eS+1);
        if(e != '}')
            throw new jpl::_parser::_json::_exception::JSONParseException("Json String does not terminate with }");
        return jpl::_parser::_json::parseJSONObjectByString(b, parseName, tabs+1);
    }else if(s == '['){
        size_t eS = jpl::_utils::_string::getIndexGroupOver(buffer, std::regex("\\["), std::regex("\\]"));
        char e = buffer.at(eS);
        std::string b = jpl::_utils::_string::trim( buffer.substr(1, eS) ); //it also remove opening and closing bracket 
        jpl::_parser::_json::stct(buffer, eS+1);
        if(e != ']')
            throw new jpl::_parser::_json::_exception::JSONParseException("Json String does not terminate with ]");
        return jpl::_parser::_json::parseJSONArrayByString(b, parseName, tabs+1);
    }else if(s == '"'){
        return jpl::_parser::_json::parseJSONFieldByString(buffer, parseName, tabs+1);
    }
    throw new jpl::_parser::_json::_exception::JSONParseException(s + " is not a valid char at the beginning of a json file");
}

jpl::_parser::_json::JSONArray* jpl::_parser::_json::parseJSONArrayByString(std::string &buffer, bool parseName, size_t tabs){
        std::string name = "";
        if(parseName){
            buffer = jpl::_utils::_string::startTrim(buffer);
            size_t beg = jpl::_utils::_string::findFirstOf(buffer, std::regex("\"")).pos;
            if(beg == buffer.size())
                throw new jpl::_parser::_json::_exception::JSONParseException("Could not parse JSONArray: name begins error");
            size_t end = jpl::_utils::_string::findFirstOf(buffer.substr(1), std::regex("\"")).pos;
            if(end == buffer.size()+1)
                throw new jpl::_parser::_json::_exception::JSONParseException("Could not parse JSONArray: name end error");
            name = buffer.substr(beg+1,end);
            buffer = jpl::_utils::_string::startTrim(buffer.substr(end+1));
        }else{
            buffer = jpl::_utils::_string::startTrim(buffer);   //Remove any \n\t or space
        }
        
    jpl::_parser::_json::JSONArray* root = new jpl::_parser::_json::JSONArray(name, tabs);
    while(!buffer.empty()){
        void* ptr = parseJSONString(buffer, false, tabs);
        if(static_cast<jpl::_parser::_json::JSONArray*>(ptr)){
            root->addJSONArray( (jpl::_parser::_json::JSONArray*)ptr );
        }else if(static_cast<jpl::_parser::_json::JSONObject*>(ptr)){
            root->addJSONObject( (jpl::_parser::_json::JSONObject*)ptr );
        }else if(static_cast<jpl::_parser::_json::JSONField*>(ptr)){
            root->addJSONField( (jpl::_parser::_json::JSONField*)ptr );
        }
    }
    return root;
}

jpl::_parser::_json::JSONObject* jpl::_parser::_json::parseJSONObjectByString(std::string &buffer, bool parseName, size_t tabs ){
        std::string name = "";
    if(parseName){
        buffer = jpl::_utils::_string::startTrim(buffer);
        size_t beg = jpl::_utils::_string::findFirstOf(buffer, std::regex("\"")).pos;
        if(beg == buffer.size())
            throw new jpl::_parser::_json::_exception::JSONParseException("Could not parse JSONObject: name begins error");
        size_t end = jpl::_utils::_string::findFirstOf(buffer.substr(1), std::regex("\"")).pos;
        if(end == buffer.size()+1)
            throw new jpl::_parser::_json::_exception::JSONParseException("Could not parse JSONObject: name end error");
        name = buffer.substr(beg+1,end);
        buffer = jpl::_utils::_string::startTrim(buffer.substr(end+1));
    }else{
        buffer = jpl::_utils::_string::startTrim(buffer);   //Remove any \n\t or space
    }

    jpl::_parser::_json::JSONObject* root = new jpl::_parser::_json::JSONObject(name, tabs);
    while(!buffer.empty()){
        void* ptr = parseJSONString(buffer, true, tabs);
        if(static_cast<jpl::_parser::_json::JSONArray*>(ptr)){
            root->addJSONArray( (jpl::_parser::_json::JSONArray*)ptr );
        }else if(static_cast<jpl::_parser::_json::JSONObject*>(ptr)){
            root->addJSONObject( (jpl::_parser::_json::JSONObject*)ptr );
        }else if(static_cast<jpl::_parser::_json::JSONField*>(ptr)){
            root->addJSONField( (jpl::_parser::_json::JSONField*)ptr );
        }
    }
    return root;
}

jpl::_parser::_json::JSONField* jpl::_parser::_json::parseJSONFieldByString(std::string &buffer, bool parseName, size_t tabs){
    buffer = jpl::_utils::_string::trim(buffer);
    if(buffer.empty())
        throw new jpl::_parser::_json::_exception::JSONParseException("Trying to parse an empty string");
    if(buffer.at(0) != '"')
        throw new jpl::_parser::_json::_exception::JSONParseException("JSONField does not seems to begin with dobule-quotes");
    size_t div = jpl::_utils::_string::findFirstOf(buffer.substr(1), std::regex("\"")).pos+1;
    std::string name = "", fasS = ""; //Field as String
    if(parseName){
        name = buffer.substr(1, div-1);
        buffer = jpl::_utils::_string::startTrim(buffer.substr(2+div));
        div = jpl::_utils::_string::findFirstOf(buffer, std::regex(":")).pos;
        fasS = jpl::_utils::_string::trim( buffer.substr(div+1, buffer.size()) );
    }else{
        fasS = buffer.substr(1, buffer.size()-1);
    }
    return new jpl::_parser::_json::JSONFieldString(name, tabs, fasS);
}

void jpl::_parser::_json::stct(std::string &buffer, size_t i){
    buffer = jpl::_utils::_string::trim(buffer.substr(i)); //substring and trim
    if(buffer.size() > 0){
        if(buffer.at(0) == ','){
            buffer = jpl::_utils::_string::trim(buffer.erase(0,1));   //remove comma and trim
        }
        if(!jpl::_utils::_string::startWith(buffer, jpl::_parser::_json::stct_regex)){
            throw new jpl::_parser::_json::_exception::JSONParseException(buffer.at(0) + " is not a valid char for JSONobject/JSONArray/JSONField beginning");
        }
    }
}