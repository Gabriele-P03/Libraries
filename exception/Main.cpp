#include "src/runtime/SocketException.hpp"
#include <sys/socket.h>

void f(){
    
    char* buffer = new char[2];

    recv(1, buffer, 2, 0);

    throw new SocketException(1);
}

int main(){

    try{
        f();
    }catch(const jpl::_exception::SocketException* ex){
        std::cout<<*ex;
    }

    return 0;
}