/**
 * It provides an std::vector of pointers to Client (those ones created by accept() of MainServerSocket).
 * 
 * Here you are some functions which take care about adding, removing and checking these instances of Clients.
 * 
 * If you wanna that new client has to be checked if it has permissions to join server, you should call loadPermission giving ifstream of the file where 
 * they will be read from. If you're not interested to extend this class, be aware that this one read only from CSV file as follow:
 *      name_client,ip,root
 * 
 * If loadPermission() has not been called, every client will be able to join to the server (but with no root permission).
 * 
 * This class offers a poor quality of security, it is unreliable; then it is recommended to extends this class and implement your more fitting 
 * security system.
 * 
 * The structure of permission of this class provides (as you have read above) name_client,ip,root; then if you wanan implement your own security system,
 * apart to override loadPermission(), you should do isClientAllowed(), too; but, even if you do not need to override addNewClient(), you should at least 
 * copy-paste the parent function body, in order to make it call the overriden functions.
 * 
 * @date 2023-01-26
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef CLIENT_LIST_CONTROLLER_HPP
#define CLIENT_LIST_CONTROLLER_HPP

#include "Client.hpp"
#include <vector>
#include <jpl/logger/PrintLogger.hpp>

#ifdef __linux__
    #include <arpa/inet.h>
    #define SHUTDOWN_SOCKET_JPL SHUT_RDWR   //SHUT_RDWR to stops receiving and sending when a socket connection canno be enstabilished
#elif defined(__WIN32)
    #include <ws2tcpip.h>
    #define SHUTDOWN_SOCKET_JPL SD_BOTH     //SD_BOTH to stops receiving and sending when a socket connection canno be enstabilished
#endif

#include <fstream>

namespace jpl{

    namespace _socket{

        extern std::string getClientIp(Client* client); 

        class ClientListController{


            protected:

                /**
                 * All permissions available for a Client
                 * 
                 */
                struct Permission;

                std::vector<Client*> clients;

                /**
                 * If permissions have not been loaded, it will be nullptr
                 */
                std::vector<Permission>* permissions;

                bool checkPermission;

                virtual bool isClientAllowed(Client* client);


            public:
                ClientListController();

                virtual void loadPermission(std::ifstream* stream);

                virtual void addNewClient(Client* &client);

        };
    }
}

#endif