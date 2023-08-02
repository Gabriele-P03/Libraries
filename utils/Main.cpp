#include "src/debug/stacktrace/Stacktrace.hpp" 
#include <jpl/exception/runtime/RuntimeException.hpp>

void f(){
    throw new std::exception;
}

int main(){

    try{
        f();
    }catch( std::exception* ex ){
        std::cout<<"Bah"<<std::endl;
        jpl::_utils::_debug::Stacktrace st(0, 10);
        }

    return 0;
}