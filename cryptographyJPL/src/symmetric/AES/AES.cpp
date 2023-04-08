#include "AES.hpp"

jpl::_cypher::_symmetric::AES::AES(std::string* raw_key, const jpl::_cypher::_symmetric::AES_TYPE* aes_type) : aes_type(aes_type){

    this->checkKey(raw_key);
}

void jpl::_cypher::_symmetric::AES::checkKey(std::string* raw_key){

    if(raw_key->size() != aes_type->getLength()/8)
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_KEY_SIZE_ERROR;
    else
        this->raw_key = raw_key;
}

jpl::_cypher::_symmetric::AES_TYPE jpl::_cypher::_symmetric::AES::getAESType(){
    return *this->aes_type;
}

jpl::_cypher::_symmetric::AES::~AES(){

    delete this->raw_key;
}