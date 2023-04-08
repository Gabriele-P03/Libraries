#include "AESType.hpp"

jpl::_cypher::_symmetric::AES_TYPE::AES_TYPE(const unsigned short index, const unsigned short bits_length, const unsigned short rounds) : 
    index(index), bits_length(bits_length), rounds(rounds){

}

const jpl::_cypher::_symmetric::AES_TYPE* jpl::_cypher::_symmetric::AES_TYPE::AES128 = 
    new jpl::_cypher::_symmetric::AES_TYPE(0, 128, 10);

const jpl::_cypher::_symmetric::AES_TYPE* jpl::_cypher::_symmetric::AES_TYPE::AES192 = 
    new jpl::_cypher::_symmetric::AES_TYPE(1, 192, 12);

const jpl::_cypher::_symmetric::AES_TYPE* jpl::_cypher::_symmetric::AES_TYPE::AES256 = 
    new jpl::_cypher::_symmetric::AES_TYPE(2, 256, 14);