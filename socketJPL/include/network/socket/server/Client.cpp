#include "Client.hpp"

jpl::_socket::Client::Client(unsigned int socket_fd, sockaddr_in addr, socklen_t sock_len){

    this->socket_fd = socket_fd;
    this->addr = addr;
    this->sock_len = sock_len;
}



unsigned int jpl::_socket::Client::getSocketFD(){
    return this->socket_fd;
}

sockaddr_in* jpl::_socket::Client::getSocketAddress(){
    return &this->addr;
}

socklen_t jpl::_socket::Client::getSocketLength(){
    return this->sock_len;
}