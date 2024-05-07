#include "Main.hpp"

using namespace jpl::_utils::_string;

int main(){

    1- PASSA QUERYSTACKTRACE IN CPP FILE...
    2- LE FUNZIONI STATICHE DI LOGGERWRAPPER DEVONO ESSERE DICHIARATE INLINE ALTRIMENTI CAUSA MULTIPLE DEF PER CMAKE

    std::string src = "{{}__{}{{}}";
    std::cout<<getIndexGroupOver(src, std::regex("\\{"), std::regex("\\}"));
    
    //jpl::_utils::_collections::_list::LinkedList<std::string>* vec = split(src, std::regex("\"[ ]*:"));
    return 0;
}