#include "src/runtime/IOException.hpp"

void f(){
    
    throw new jpl::_exception::IOException();
}

int main(){

    try{
        f();
    }catch( jpl::_exception::IOException* ex){
        std::cout<<ex->what();
    }

    return 0;
}