/**
 *
 * A Client is made up once accept() call return a new connection enstabilished
 * 
 * As you can read from MainServerSocket, all instance of this class (or its inherited one) are stored inside an std::vector<Client*>
 * 
 * @date 2023-01-26
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef MAIN_CLIENT_SOCKET_JPL
#define MAIN_CLIENT_SOCKET_JPL

#ifdef __linux__
    #include <sys/socket.h>
    #include <netdb.h>
#elif defined(__WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>
#endif



namespace jpl{

    namespace _socket{

        class Client{

            private:


            protected: 

                unsigned int socket_fd; 
                sockaddr_in addr;
                socklen_t sock_len;

            public:

                Client(unsigned int socket_fd, sockaddr_in addr, socklen_t sock_len);

                unsigned int getSocketFD();

                sockaddr_in* getSocketAddress();

                socklen_t getSocketLength();

        };
    }
}

#endif
