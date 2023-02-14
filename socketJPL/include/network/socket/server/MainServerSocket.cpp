#include "MainServerSocket.hpp"

jpl::_socket::MainServerSocket::MainServerSocket(unsigned int port) : jpl::_socket::MainServerSocket(port, AF_INET, SOCK_STREAM, IPPROTO_TCP){}
jpl::_socket::MainServerSocket::MainServerSocket(unsigned int port, int domain, int type, int protocol) : 
    jpl::_socket::MainSocket(port, domain, type, protocol){

        this->max_queue = 0;
        this->flagLoop = true;
        this->clientListController = nullptr;
    }

void jpl::_socket::MainServerSocket::loopAccept(){

    while(flagLoop){

        sockaddr_in addr;
        socklen_t len;
        int res = accept(this->socket_fd, (struct sockaddr*)&addr, &len);
        if(res < 0){
            this->overrideNewError();
            jpl::print("A client attempted to connect with error: " + std::to_string(this->getLastError()));
        }else{
            //Checking for permission to connect to the server is done by ClientListController
            Client* client = new Client(res, addr, len);
            this->clientListController->addNewClient(client);
        }

    }
}

void* jpl::_socket::MainServerSocket::startThread(void* instance){
    ((MainServerSocket*)instance)->loopAccept();

    return NULL;
}

int jpl::_socket::MainServerSocket::startLoopAcceptThread(){

    if(this->clientListController == nullptr){
        jpl::print("You cannot start accept loop without an instance of ClientListController", "ERR");
        return -1;
    }

    //Solo per debugging: poi commenta loopAccept e decommenta il resto

    this->loopAccept();
    /*
    int res = pthread_create(&this->loopAccept_pthread_id, NULL, jpl::_socket::MainServerSocket::startThread, this);
    if(res == 0){
        res = pthread_detach(this->loopAccept_pthread_id);
    }
    
    return res;
    */

   return 0;
}

bool jpl::_socket::MainServerSocket::isLoopRunning(){
    return this->flagLoop;
}

void jpl::_socket::MainServerSocket::setLoopState(bool flagLoop){

    this->flagLoop = flagLoop;
}

jpl::_socket::MainServerSocket::~MainServerSocket(){

    delete this->clientListController;
}

void jpl::_socket::MainServerSocket::setClientListController(jpl::_socket::ClientListController* clientListController){
    this->clientListController = clientListController;
}

std::string jpl::_socket::getClientIp(jpl::_socket::Client* client){
    
    //Let's get ip of the client
                
    sa_family_t fam = client->getSocketAddress()->sin_family;
    //INET6_ADDRSTRLEN is greater than INET one, but if iPv6 is not supported, than INET6_ADDRSTRLEN is defined as 0 
    unsigned int size = INET6_ADDRSTRLEN > INET_ADDRSTRLEN ? INET6_ADDRSTRLEN : INET_ADDRSTRLEN;
    char s[INET_ADDRSTRLEN];
    //inet_ntop(fam, client->getSocketAddress(), s, fam == AF_INET6 ? INET6_ADDRSTRLEN : INET_ADDRSTRLEN);
    #ifdef __linux__
        inet_ntop(AF_INET, client->getSocketAddress(), s, INET_ADDRSTRLEN);
    #elif defined(__WIN32)
        sockaddr_in* tmp = client->getSocketAddress(); 
        WSAAddressToStringA( (struct sockaddr*)tmp, client->getSocketLength(), NULL, s, (LPDWORD)&size);
    #endif

    return std::string(s);
}