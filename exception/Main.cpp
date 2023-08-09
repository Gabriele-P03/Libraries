#include "Main.hpp"


void f(){
    
    throw new jpl::_exception::IOException();
}

int main(){

    try{
        f();
    }catch( jpl::_exception::IOException* ex){
        jpl::_logger::print(ex->getStacktraceAsString());
    }

    return 0;
}