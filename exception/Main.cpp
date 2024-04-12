#include "Main.hpp"

void f(){
    
    throw new jpl::_exception::IOException();
}

int main(){

    try{
        std::cout<<"Prova...";
        f();
    }catch( jpl::_exception::IOException* ex){
        
    }

    return 0;
}