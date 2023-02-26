#include "TDES.hpp"

jpl::_cypher::_symmetric::TDES::TDES(std::string key1, std::string key2, std::string key3){

    this->first = new jpl::_cypher::_symmetric::DES(key1);
    this->second = new jpl::_cypher::_symmetric::DES(key2);
    this->third = new jpl::_cypher::_symmetric::DES(key3);
}



//ECB part
std::string* jpl::_cypher::_symmetric::TDES::ecb_encrypt(std::string plain_text){
    std::string* buffer1 = first->ecb_encrypt(plain_text);
    std::string* buffer2 = second->ecb_decrypt(*buffer1);
    delete buffer1;
    std::string* buffer3 = third->ecb_encrypt(*buffer2);
    delete buffer2;
    return buffer3;
}

std::string* jpl::_cypher::_symmetric::TDES::ecb_decrypt(std::string cyphered_text){
    std::string* buffer3 = third->ecb_decrypt(cyphered_text);
    std::string* buffer2 = second->ecb_encrypt(*buffer3);
    delete buffer3;
    std::string* buffer1 = first->ecb_decrypt(*buffer2);
    delete buffer2;
    return buffer1;
}

/**
 * Il TDES-CBC
 * 
 * le tre fasi e-d-e devono essere chiamate per ogni blocco
 * 
 * tdes.first.set_CBC_IV(iv)
 * 
 *  while(plain)
 *      blocco
 *      tdes(blocco)
 * 
 */


//CBC part
std::string* jpl::_cypher::_symmetric::TDES::cbc_encrypt(std::string plain_text){
    std::string* buffer1 = first->cbc_encrypt(plain_text);
    second->set_CBC_IV(  );
    std::string* buffer2 = second->cbc_decrypt(*buffer1);
    delete buffer1;
    std::string* buffer3 = third->cbc_encrypt(*buffer2);
    delete buffer2;
    return buffer3;
}

std::string* jpl::_cypher::_symmetric::TDES::cbc_decrypt(std::string cyphered_text){
    std::string* buffer3 = third->cbc_decrypt(cyphered_text);
    std::string* buffer2 = second->cbc_encrypt(*buffer3);
    delete buffer3;
    std::string* buffer1 = first->cbc_decrypt(*buffer2);
    delete buffer2;
    return buffer1;
}


void jpl::_cypher::_symmetric::TDES::set_CBC_IV(std::string IV){
    this->first->set_CBC_IV(IV);
}

jpl::_cypher::_symmetric::TDES::~TDES(){
    delete first;
    delete second;
    delete third;
}

