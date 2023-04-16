#include "Main.hpp"

int main(){


    jpl::_security::_cypher::_symmetric::TDES* des = new jpl::_security::_cypher::_symmetric::TDES("abcdefgh", "ijklmnop", "qrstuvwx");
    des->set_CBC_IV("abcdefgh");
    std::string* enc = des->cbc_encrypt("ciao1234");  
    std::string* dec = des->cbc_decrypt(*enc);
    std::cout<<*dec;

    return 0;
}