/**
 * This is the abstraction header file of the socket class.
 * Cross-Compiled windows - linux.
 * 
 * The implicit constructor are meant to be for internet connection with a TCP connection.
 * 
 * If you need another kinda of it, you should use the general constructor.
 * Since General Constructor needs the three main parameters (domain, type, protocol), you can aven use it in order
 * to communicate via Bluetooth; but be aware! This framework has been thought as game development one, then it does not 
 * provide any feature for other type of communication. 
 * 
 * This class definition has any private member fields, then you may extend it in order to develop extra functions (e.g. to check available bluetooth radio on the device).
 * 
 * Since this class could be used either as client or as server, you can check what type of socket it is  
 * 
 * Once you have called _recv() or _send(), if some errors occurred, they return -1 and the error is stored into last_error and error_occurred is set to true. 
 * You can get it calling getLastError(); but pay attention: once done, both fields are set as respectively to '0' and 'false'. 
 * If you're under a windows kernel, WSACleanup() will be also called when an error occurred; since it may fail, the error code will be stored in last_error,
 * then the error code is overriden, giving more importance to WSACleanup()'s error code.
 * 
 * Info about Server Mode:
 *      Once you have called constructor, you have to invoke listen() function by yourself, the same goes for accept()
 * 
 * 
 * If you're working on a windows kernel, notice that winsock2.h needs to be included before windows.h; then, if you're using GameLibrary or some others 
 * frameworks which include this last one, you should include MainSocket.hpp even in your Main end before any others header files.
 * But, since this socket interface has been thougth to work with GameLibrary framework, and this one has a Logger class, you should, at least, include 
 * Logger before MainSocket, 'cause info, warnings or errors occurred are printed in console, and in logger (if you're working with my framework)
 * 
 * If you're using Explicit Constructor for a tcp/udp connection, a tip for you is to not use either '0' or IPPRTOTO_IP as protocol field, it could
 * cause some errors not shown during binding/connection. In fact, I've used IPPROTO_TCP for SOCK_STREAM (for UDP - SOCK_DGRAM - you should use IPPROTO_UDP).
 * For more information about either explicit or implicit protocol, take a look at documentation. 
 * 
 * If you are interested to use Logger of GameLibrary framework, you have to define USE_LOGGER_JPL before including any extension of this class
 * 
 * @date 2023-01-20
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef MAINSOCKET_JPL
#define MAINSOCKET_JPL

#ifdef __linux__
    
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>

#elif defined(__WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>

    //Macro used by MAKEWORD in order to request the max version of winsock
    #define FST_V 2
    #define SND_V 2

#else
    #error "The kernel you're trying to develop on is unknown"

#endif

#include <string.h> //Only for memset
#include <string>

#include <jpl/logger/PrintLogger.hpp>

namespace jpl{
    
    namespace _socket{


        class MainSocket{

            private:

                typedef bool MODE_SOCKET;
                static const MODE_SOCKET SERVER_MODE_SOCKET;
                static const MODE_SOCKET CLIENT_MODE_SOCKET;

            protected:
                

                unsigned int port;

                //Contains the last error code occurred
                int last_error;
                //Tells you if an error occurred since last call of getLastError()
                bool error_occurred;

                //File descriptor of the socket created
                unsigned int socket_fd;

                //Mode of the socket
                MODE_SOCKET _mode_socket;
                //Domain, type and protocol
                int domain, type, protocol;

                //Ip as string of the server target machine. Empty if this is a SERVER_SOCKET;
                std::string server_ip;
                
                /**
                * If this socket object is in client mode, this fields contains info about server target machine.
                * If it is in server mode, it will be nullptr
                */
                struct addrinfo* server_addr;

                #ifdef _WIN32
                
                    WSAData wsaData;
                #endif

                /**
                 * Set socket with the parameter that have been given to constructor 
                 * 
                 * @return 0 for succes otherwise -1 
                 */
                virtual int setSocket();

                /**
                 * Called by member functions once an error occurred.
                 * It set error_occurred as true and stores into last_error the code 
                 */
                virtual void overrideNewError();

            public:

                /**
                 * Server Constructor
                 * Implicit for AF_INET, SOCK_STREAM, 0 as protocol
                 * 
                 * @param port 
                 */
                MainSocket(unsigned int port);

                /**
                 * General constructor of the socket
                 * 
                 * @param port
                 * @param domain
                 * @param type
                 * @param protocol
                 */
                MainSocket(unsigned int port, int domain, int type, int protocol);

                /**
                 * Client Constructor 
                 * Implicit for AF_INET, SOCK_STREAM, 0 as protocol
                 * 
                 * @param ip of the server
                 * @param port 
                 */
                MainSocket(std::string ip, unsigned int port);

                /**
                 * General constructor for client
                 * 
                 * @param ip of the server
                 * @param port 
                 * @param domain 
                 * @param type 
                 * @param protocol
                 */
                MainSocket(std::string ip, unsigned int port, int domain, int type, int protocol);

                /**
                 * Send to the target 
                 * 
                 * 
                 * @param socket_fd_target fd of the target machine socket
                 * @param buffer 
                 * @param size 
                 * 
                 * @return how many bytes have been sent
                 */
                virtual inline int _send(unsigned int socket_fd_target, const char* buffer, std::size_t size, int _flags){

                    std::size_t sent = send(socket_fd_target, buffer, size, _flags);
                
                    if(sent != size)
                        this->overrideNewError();
                    
                    return sent;
                }

                /**
                 * Stores into buffer bytes received. Its amount is copied into size field
                 * 
                 * @param socket_fd_target
                 * @param buffer 
                 * @param size size of the buffer
                 * @return amount of bytes stored into buffer or -1 in case of error
                 * 
                 */
                virtual inline int _recv(unsigned int socket_fd_target, char* & buffer, std::size_t size, int _flags){

                    ssize_t _s = recv(socket_fd_target, buffer, size, _flags);

                    if(_s < 0)
                        this->overrideNewError();
                    else if(_s == 0){
                        //Unexpected Connection closed by the target 
                        return 0;
                    }
                    return _s;
                }

                inline MODE_SOCKET getModeSocket(){
                    return this->_mode_socket;
                }

                inline std::string getServerTargetMachine(){
                    return this->server_ip;
                }

                virtual inline bool isError(){
                    return this->error_occurred;
                }

                /**
                 * Return the last error occurred and reset flag
                 * 
                 * @return int 
                 */
                virtual inline int getLastError(){
                    this->error_occurred = false;
                    this->last_error = 0;
                    return this->last_error;
                }

                inline int getDomain(){
                    return this->domain;
                }

                inline int getType(){
                    return this->type;
                }

                inline int getProtocol(){
                    return this->protocol;
                }

                inline int getSocketFD(){
                    return this->socket_fd;
                }

                ~MainSocket();
        };

    }

}

#endif
