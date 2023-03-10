#include "AES.hpp"
jpl::_cypher::_symmetric::AES_TYPE::AES_TYPE(unsigned short index, unsigned short key_length_bits) : 
    index(index), key_length_bits(key_length_bits) {

}

const jpl::_cypher::_symmetric::AES_TYPE jpl::_cypher::_symmetric::AES::aes_128 = jpl::_cypher::_symmetric::AES_TYPE(0, 128);
const jpl::_cypher::_symmetric::AES_TYPE jpl::_cypher::_symmetric::AES::aes_192 = jpl::_cypher::_symmetric::AES_TYPE(0, 192);
const jpl::_cypher::_symmetric::AES_TYPE jpl::_cypher::_symmetric::AES::aes_256 = jpl::_cypher::_symmetric::AES_TYPE(0, 256);

jpl::_cypher::_symmetric::AES::AES(std::string raw_key, const jpl::_cypher::_symmetric::AES_TYPE* aes_type){

    this->aes_type = aes_type;
    this->checkKey(raw_key);
}

void jpl::_cypher::_symmetric::AES::checkKey(std::string raw_key){
    std::size_t size_raw_key = raw_key.size();
    if(size_raw_key != this->aes_type->key_length_bits/8){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_KEY_SIZE_ERROR;
    }else{
        this->raw_key = raw_key;
    }
}

jpl::_cypher::_symmetric::AES_TYPE jpl::_cypher::_symmetric::AES::getAESType(){
    return *this->aes_type;
}

jpl::_cypher::_symmetric::AES::~AES(){
    delete this->aes_type;
}