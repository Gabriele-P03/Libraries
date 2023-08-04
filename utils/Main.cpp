#include "src/debug/stacktrace/Stacktrace.hpp" 

void f1(){
    jpl::_utils::_debug::Stacktrace sta;
    std::cout<<sta;
}

void f2(){

}

void f(){

    f1();
    
    f2();
}

int main(){

    f();


    return 0;
}