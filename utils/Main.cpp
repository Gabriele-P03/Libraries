#include "src/ErrorUtils.hpp"

#include <iostream>

int main(){

    std::string s = jpl::_utils::_error::_GetLastErrorAsString();

    std::cout<<s;


    return 0;
}