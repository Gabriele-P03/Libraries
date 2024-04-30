#include "src/StringUtils.hpp"
#include <iostream>

int main(){

    std::string src = "ProvaPa\\\"1\\\"\"";

    std::cout<<src<<std::endl<<jpl::_utils::_string::findFirstOf(src, std::regex("a"))<<std::endl<<jpl::_utils::_string::findLastOf(src, std::regex("a"));
}