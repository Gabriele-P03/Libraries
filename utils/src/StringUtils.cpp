#include "StringUtils.hpp"

jpl::_utils::_collections::_list::LinkedList<std::string>* jpl::_utils::_string::split(const std::string &src, const std::regex& regex){
    jpl::_utils::_collections::_list::LinkedList<std::string>* vec = new jpl::_utils::_collections::_list::LinkedList<std::string>();
    auto word_begin = std::sregex_token_iterator(src.begin(), src.end(), regex, -1);
    auto word_end = std::sregex_token_iterator();
    for(; word_begin != word_end; ++word_begin){
        std::string match_string = *word_begin;
        vec->add(match_string);
    }
    return vec;
}


size_t jpl::_utils::_string::getIndexGroupOver(std::string src, const std::regex &o, const std::regex &c){
    size_t i = 0, count = 0;
    do{
        jpl::_utils::_string::RegexMatch ms = jpl::_utils::_string::findFirstOf(src, o);
        jpl::_utils::_string::RegexMatch me = jpl::_utils::_string::findFirstOf(src, c);
        if(me.pos == src.size())
            break;
        if(ms.pos == src.size() || ms.pos > me.pos){
            count += me.pos + me.length;
            src = src.substr(me.pos + me.length);
            i--;
            if(i == 0) break;
        }else if(ms.pos < me.pos){
            count += ms.pos + ms.length;
            src = src.substr(ms.pos + ms.length);
            i++;
        }else
            return ms.pos;
    }while(i > 0);
    if(i > 0)
        throw jpl::_exception::RuntimeException("Amount of opening chars do not correspond to closing one");
    return count-1;
}