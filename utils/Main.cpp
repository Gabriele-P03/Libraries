
#include "Main.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;

int main(){

    std::string s = std::string("!\"ciao\"!!\"ciao\"!");
    _string::RegexMatch m = _string::getIndexGroupOver(s, std::regex("!"), std::regex("!!"));
}