
#include "Main.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;


void z(){
throw new _exception::RuntimeException("Prova diu Prova diu Prova diu Prova diu Prova diu Prova diuProva diu");
}

void y(){
    z();
}

void x(){
    y();
}


int main(){

    x();
}