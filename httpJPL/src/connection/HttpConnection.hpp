/**
 * A connection is enstabilished between this endpoint and the given host.
 * This is a uncrypted connection, then it is very unsuggested to send any credentials via this type; you oughta use HttpsConnection()
 * 
 * @date 2023-02-09
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef HTTP_CONNECTION_JPL
#define HTTP_CONNECTION_JPL

#include <jpl/network/socket/MainSocket.hpp>

//As we already know, http does listen on 80 port. RFC 7540 (Section 3)
#define HTTP_STANDARD_PORT_JPL 80

namespace jpl{

    namespace _connection{
        
        //typedef of port
        typedef unsigned int PORT;
    }

    namespace _http{

        class HttpConnection : public _socket::MainSocket{

            public:

                /**
                 * Create a new connection between this endpoint where this framework is used and the HOST identified by _HOST.
                 * The socket will listen on _PORT port
                 * 
                 * @param host 
                 * @param _PORT 
                 */
                HttpConnection(std::string _HOST, _connection::PORT _PORT);
        };
    }
}


#endif
