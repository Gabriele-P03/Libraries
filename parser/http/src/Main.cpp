#include "Main.hpp"

int main(){

    jpl::_http::HttpConnection* httpConn = new jpl::_http::HttpConnection("www.google.com", HTTP_STANDARD_PORT_JPL);

    return 0;
}