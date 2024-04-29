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

jpl::_parser::_json::JSONArray* jpl::_parser::_json::parseJSONArrayByString(std::string buffer){
    return new jpl::_parser::_json::JSONArray("array", 1);
}

jpl::_parser::_json::JSONObject* jpl::_parser::_json::parseJSONObjectByString(std::string buffer){
    return new jpl::_parser::_json::JSONObject("object", 1);
}