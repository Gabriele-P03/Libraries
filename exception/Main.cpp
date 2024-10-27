#define USE_STACKTRACE_W_EXCEPTION_JPL
#define AUTO_LOG_EXCEPTION_JPL
#include <jpl/logger/LoggerWrapper.hpp>
#include "src/runtime/IllegalStateException.hpp"

void f(){
    
    throw jpl::_exception::IllegalStateException("Prova");
}

int main(){

    f();

    return 0;
}