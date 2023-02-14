#include "include/network/socket/server/MainServerSocket.hpp"

#include <jpl/files/FilesUtils.hpp>

int main(){

    jpl::_socket::MainServerSocket* socket = new jpl::_socket::MainServerSocket(8080);


    jpl::_socket::ClientListController* controller = new jpl::_socket::ClientListController();

    std::fstream* file = new std::fstream;
    jpl::_files::getLocalFile("permissions.txt", std::ios_base::in, &file);
    controller->loadPermission((std::ifstream*)file);

    socket->setClientListController(controller);
    socket->setListenQueue(5);

    return 0;
}