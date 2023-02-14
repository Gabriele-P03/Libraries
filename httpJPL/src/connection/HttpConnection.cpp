#include "HttpConnection.hpp"

jpl::_http::HttpConnection::HttpConnection(std::string _HOST, jpl::_connection::PORT _PORT)
    : jpl::_socket::MainSocket(_HOST, _PORT){


}