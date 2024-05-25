#include "Main.hpp"

int main(){

    std::string src = "{{}__{}{{}}";
    std::cout<<jpl::_utils::_string::getIndexGroupOver(src, std::regex("\\{"), std::regex("\\}"));
    
    //jpl::_utils::_collections::_list::LinkedList<std::string>* vec = split(src, std::regex("\"[ ]*:"));
    return 0;

}