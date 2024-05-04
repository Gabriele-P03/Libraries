#include "StringUtils.hpp"

std::vector<std::string>* jpl::_utils::_string::split(std::string src, std::regex regex, const unsigned long long maxSize){
    std::vector<std::string>* vec = new std::vector<std::string>;
    auto word_begin = std::sregex_token_iterator(src.begin(), src.end(), regex, -1);
    auto word_end = std::sregex_token_iterator();
    unsigned long count = 0;
    for(; word_begin != word_end; ++word_begin){

        std::string match_string = *word_begin;
        vec->push_back(match_string);
        if(maxSize > 0){
            if(++count > maxSize)
                break;
        }
    }
    return vec;
}
std::vector<std::string>* jpl::_utils::_string::split(std::string src, std::regex regex){
    return jpl::_utils::_string::split(src, regex, std::string::npos);
}

size_t jpl::_utils::_string::getIndexGroupOver(std::string src, std::regex o, std::regex c){
    size_t i = 0, count = 0;
    do{
        jpl::_utils::_string::RegexMatch ms = jpl::_utils::_string::findFirstOf(src, o);
        jpl::_utils::_string::RegexMatch me = jpl::_utils::_string::findFirstOf(src, c);
        if(ms.pos == src.size() || ms.pos > me.pos){
            count += me.pos + me.length;
            src = src.substr(me.pos + me.length);
            if(i > 0) i--;
            else break;
        }else if(ms.pos < me.pos){
            count += ms.pos + ms.length;
            src = src.substr(ms.pos + ms.length);
            i++;
        }else
            return ms.pos;
    }while(i > 0);
    return count-1;
}