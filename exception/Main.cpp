#include "Main.hpp"

void f(){
    
    throw new jpl::_exception::IOException();
}

int main(){

    f();

    return 0;
}