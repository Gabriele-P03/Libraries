#include "src/runtime/FileNotFoundException.hpp"

void f(){
    throw new FileNotFoundException("ok");
}

int main(){

    f();

    return 0;
}