#include "JSONUtils.hpp"

jpl::_parser::_json::JSONField* jpl::_parser::_json::parseFieldByString(std::string buffer){
    return nullptr;
}

std::string* jpl::_parser::_json::smartFieldDivide(std::string f){

    char s = ':';
    bool flag = false;
    for(size_t i = 0; i < f.size(); i++){
        char c = f.at(i);
        if(c == '"'){
            flag = !flag;
        }else if(c == s){
            if(!flag){
                std::string* buf = new std::string[2];
                buf[0] = f.substr(1, i-1);  //Ignore opening and closing double quote
                buf[1] = f.substr(1+i);     
                return buf;
            }
        }else if(c == ' '){
            if(!flag){
                f.erase(i, 1);
            }
        }
    } 
    return nullptr;   
}