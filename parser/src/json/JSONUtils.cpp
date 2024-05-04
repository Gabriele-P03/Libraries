#include "JSONUtils.hpp"


void* jpl::_parser::_json::parseJSONString(std::string buffer){
    buffer = jpl::_utils::_string::trim(buffer);
    if(buffer.length() < 2)
        throw new jpl::_parser::_json::_exception::JSONParseException("Json String: \"" + buffer + "\" seems like that it does not have opening/closing bracket");
    char s = buffer.at(0);
    buffer = buffer.substr(1, buffer.length()-2);
    if(s == '{')
        return jpl::_parser::_json::parseJSONObjectByString(buffer);
    else if(s == '[')
        return jpl::_parser::_json::parseJSONArrayByString(buffer);
    throw new jpl::_parser::_json::_exception::JSONParseException(s + " is not a valid char at the beginning of a json file");
}

jpl::_parser::_json::JSONArray* jpl::_parser::_json::parseJSONArrayByString(std::string buffer, bool parseName, size_t tabs){
    return new jpl::_parser::_json::JSONArray("array", 1);
}

jpl::_parser::_json::JSONObject* jpl::_parser::_json::parseJSONObjectByString(std::string buffer, bool parseName, size_t tabs ){
    return new jpl::_parser::_json::JSONObject("object", 1);
}

jpl::_parser::_json::JSONField* jpl::_parser::_json::parseJSONFieldByString(std::string buffer, bool parseName, size_t tabs){
    buffer = jpl::_utils::_string::startTrim(buffer);
    if(buffer.empty())
        throw new jpl::_parser::_json::_exception::JSONParseException("Trying to parse an empty string");
    if(buffer.at(0) != '"')
        throw new jpl::_parser::_json::_exception::JSONParseException("JSONField does not seems to begin with dobule-quotes");
    std::vector<std::string>* vec = jpl::_utils::_string::split(buffer.substr(1), std::regex("\""), 2); 
    if( parseName && vec->size() != 2)
        throw new jpl::_parser::_json::_exception::JSONParseException("Encourented a non 2-sized vector while parsing json field: " + buffer);
    else if( !parseName && vec->size() != 1)
        throw new jpl::_parser::_json::_exception::JSONParseException("Encourented a non 1-sized vector while parsing json field: " + buffer);
    std::string name = "";
    if(parseName)
        name = vec->at(0);
    std::string fAsS = vec->at(vec->size()-1);
    vec->clear();
    return new jpl::_parser::_json::JSONFieldString(name, tabs, fAsS);
}