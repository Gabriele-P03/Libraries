#include "JSONUtils.hpp"


void* jpl::_parser::_json::parseJSONString(std::string &buffer, bool parseName, size_t tabs){
    buffer = jpl::_utils::_string::trim(buffer);
    if(buffer.length() < 2)
        throw new jpl::_parser::_json::_exception::JSONParseException("Json String: \"" + buffer + "\" seems like that it does not have opening/closing bracket");
    char s = buffer.at(0);
    buffer = jpl::_utils::_string::trim(buffer.substr(1, buffer.size()-2)); //Remove opening and closing bracket
    if(s == '{'){
        size_t eS = jpl::_utils::_string::getIndexGroupOver(buffer, std::regex("{"), std::regex("}"));
        char e = buffer.at(eS);
        if( != '}')
            throw new jpl::_parser::_json::_exception::JSONParseException("Json String does not terminate with }");
        return jpl::_parser::_json::parseJSONObjectByString(buffer, parseName, tabs);
    }else if(s == '['){
        size_t eS = jpl::_utils::_string::getIndexGroupOver(buffer, std::regex("["), std::regex("]"));
        if(e != ']')
            throw new jpl::_parser::_json::_exception::JSONParseException("Json String does not terminate with ]");
        return jpl::_parser::_json::parseJSONArrayByString(buffer, parseName, tabs);
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
    void* ptr = parseJSONString(buffer, false, tabs);
    jpl::_parser::_json::JSONArray* root = new jpl::_parser::_json::JSONArray(name, tabs);

    return root;
}

jpl::_parser::_json::JSONObject* jpl::_parser::_json::parseJSONObjectByString(std::string &buffer, bool parseName, size_t tabs ){
    return new jpl::_parser::_json::JSONObject("object", 1);
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
        name = buffer.substr(1, div);
        buffer = buffer.substr(2+div);
        div = jpl::_utils::_string::findFirstOf(buffer, std::regex(":")).pos;
        fasS = jpl::_utils::_string::trim( buffer.substr(div+1, buffer.size()) );
    }else{
        fasS = buffer.substr(1, buffer.size()-1);
    }
    return new jpl::_parser::_json::JSONFieldString(name, tabs, fasS);
}