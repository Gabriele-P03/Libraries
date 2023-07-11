
#include "src/functional/supplier/Supplier.hpp"

#include <iostream>
#include <string>

using namespace jpl;
using namespace _utils;

int supplier( _functional::Supplier<int> supplier ){

    return supplier.test();
}



int main(){

    std::cout<<supplier( [] () {return 6;} );

    return 0;
}