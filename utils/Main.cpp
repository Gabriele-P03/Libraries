#include "Main.hpp"

using namespace jpl::_utils::_string;

int main(){

    std::string src = "\"prova\\\"1\\\"\":false";
    jpl::_utils::_collections::_list::LinkedList<std::string>* vec = split(src, std::regex("\""));
    return 0;
}