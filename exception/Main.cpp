#include "Main.hpp"

void f(){
    
    throw new jpl::_exception::RuntimeException();
}

int main(){

    f();

    return 0;
}