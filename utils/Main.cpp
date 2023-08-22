#include "src/debug/stacktrace/Stacktrace.hpp"

void f1(){

    std::cout<<jpl::_utils::_debug::Stacktrace();

    return;
}

void f2(){
    f1();
}


int main(){

    f2();

    return 0;
}