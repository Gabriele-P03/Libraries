#include "MainSocket.hpp"

const jpl::_network::_socket::MainSocket::MODE_SOCKET jpl::_network::_socket::MainSocket::CLIENT_MODE_SOCKET = 0;
const jpl::_network::_socket::MainSocket::MODE_SOCKET jpl::_network::_socket::MainSocket::SERVER_MODE_SOCKET = 1;

//Client constructor part
jpl::_network::_socket::MainSocket::MainSocket(std::string ip, unsigned int port) : jpl::_network::_socket::MainSocket::MainSocket(ip, port, AF_INET, SOCK_STREAM, IPPROTO_TCP){}
jpl::_network::_socket::MainSocket::MainSocket(std::string ip, unsigned int port, int domain, int type, int protocol){
    this->server_ip = ip;
    this->port = port;
    this->_mode_socket = CLIENT_MODE_SOCKET;
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;

    this->setSocket();
}

//Server constructor part
jpl::_network::_socket::MainSocket::MainSocket(unsigned int port) : jpl::_network::_socket::MainSocket(port, AF_INET, SOCK_STREAM, IPPROTO_TCP){}
jpl::_network::_socket::MainSocket::MainSocket(unsigned int port, int domain, int type, int protocol){
    this->port = port;
    this->server_ip = "";
    this->_mode_socket = SERVER_MODE_SOCKET;
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;

    this->setSocket();
}

int jpl::_network::_socket::MainSocket::setSocket(){

    /**
     * If you're under a Windows kernel, before to create a new socket processor, you must initialize winsock
     * 
     */
    #ifdef _WIN32

         //Let's initialize winsock
        int iResult;

        iResult = WSAStartup(MAKEWORD(FST_V, SND_V), &wsaData);
        if(iResult != 0){
            this->overrideNewError();
            return -1;
        }

        jpl::print("WSA started");

    #endif


        //Open socket processor with domain, type and protocol
        int res = socket(this->domain, this->type, this->protocol);
        if(res < 1){
            this->overrideNewError();
            return res;
        }
        this->socket_fd = res;  //If success, store socket fd into class member field
        jpl::print("New Socket Created");
        //Client mode
        if(this->_mode_socket == CLIENT_MODE_SOCKET){

            struct addrinfo hints;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = this->domain;
            hints.ai_socktype = this->type;
            hints.ai_protocol = this->protocol;
            this->server_addr = new addrinfo;
            res = getaddrinfo(this->server_ip.c_str(), std::to_string(this->port).c_str(), &hints, &this->server_addr);
            
            if(res != 0){
                this->overrideNewError();
                return res;
            }
            
            //Let's connect to the server target
            res = connect(this->socket_fd, this->server_addr->ai_addr, this->server_addr->ai_addrlen);
            if(res != 0){
                this->overrideNewError();
                return res;
            }
            jpl::print("Connected succesfully to " + this->server_ip);
            return 0;
        }else if(this->_mode_socket == SERVER_MODE_SOCKET){

            struct sockaddr_in tmp;
            tmp.sin_port = htons(this->port);
            tmp.sin_addr.s_addr = INADDR_ANY;
            tmp.sin_family = this->domain;
            
            this->server_addr = nullptr;
            
            res = bind(this->socket_fd,  (struct sockaddr*)&tmp, sizeof(tmp));
            if(res != 0){
                this->overrideNewError();
                return res;
            }
            print("Socket binded");
            return 0;
        }

    //Work in progress: new error code in order to catch unknown kernel detected
    return -1;
}

void jpl::_network::_socket::MainSocket::overrideNewError(){

        #ifdef __linux__
            this->last_error = errno;
        #elif defined(_WIN32)
            this->last_error = WSAGetLastError();
            int res = WSACleanup(); 
            if(res != 0){
                this->last_error = WSAGetLastError();   //It will override the last_error field
            }
        #endif

    this->error_occurred = true;
}

jpl::_network::_socket::MainSocket::~MainSocket(){

    freeaddrinfo(this->server_addr);
}