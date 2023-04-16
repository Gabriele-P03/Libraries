#include "ClientListController.hpp"

struct jpl::_network::_socket::ClientListController::Permission{
    std::string name_client;
    std::string ip;
    bool root;

    Permission(std::string name_client, std::string ip, bool root) : name_client(name_client), ip(ip), root(root){} 
};

jpl::_network::_socket::ClientListController::ClientListController(){

    this->checkPermission = false;
}

bool jpl::_network::_socket::ClientListController::isClientAllowed(jpl::_network::_socket::Client* client){
    if(this->checkPermission == false){
        jpl::print("isClientAllowed() illegal-state-exception");
        return false;
    }

    if(this->permissions != nullptr){
        if(this->permissions->size() > 0){
            for(ssize_t i = 0; i < this->permissions->size(); i++ ){
                Permission perm = this->permissions->at(i);
                std::string ip_client = jpl::_network::_socket::getClientIp(client);
                if(perm.ip == ip_client){
                    return true;
                }
            }
        }
    }

    return false;
}

void jpl::_network::_socket::ClientListController::addNewClient(jpl::_network::_socket::Client* &client){

    if(!this->checkPermission ^ (this->checkPermission && this->isClientAllowed(client))){
        this->clients.push_back(client);
    }else{
        std::string msg = "You are not allowed to connect to this server...";
        send(client->getSocketFD(), msg.c_str(), msg.size(), 0);


        if(shutdown(client->getSocketFD(), SHUTDOWN_SOCKET_JPL) == -1){
            jpl::print("Could not shutdown socket fd...", "ERR");
        }
        delete client;
    }
}

void jpl::_network::_socket::ClientListController::loadPermission(std::ifstream* stream){

    if(stream == nullptr){
        jpl::print("loadPermission called with an empty stream");
        return;
    }

    this->permissions = new std::vector<Permission>;
    std::string buffer;
    while(std::getline(*stream, buffer)){

        unsigned int first_comma_index = buffer.find_first_of(','), second_comma_index = buffer.find_last_of(',');

        if(first_comma_index == second_comma_index || first_comma_index == std::string::npos || second_comma_index == std::string::npos){
            //Some syntax errors occurred in the permissions file 
            jpl::print("Syntax-Error occurred in permission file at line " + std::to_string(this->permissions->size()) + ". Skipping line...");
            continue;
        }

        std::string name_client = buffer.substr(0, first_comma_index);
        std::string ip = buffer.substr(first_comma_index+1, second_comma_index-name_client.size()-1);

        if(name_client.empty()){
            jpl::print("name_client seems to be empty in permission file at line " + std::to_string(this->permissions->size()));
        }

        if(ip.empty()){
            jpl::print("ip seems to be empty in permission file at line " + std::to_string(this->permissions->size()) +  ". Skipping line...");
        }
        bool root = (buffer.substr(second_comma_index+1) == "1");

        this->permissions->push_back(jpl::_network::_socket::ClientListController::Permission(name_client, ip, root));

        buffer.clear();
    }

    this->checkPermission = true;
}