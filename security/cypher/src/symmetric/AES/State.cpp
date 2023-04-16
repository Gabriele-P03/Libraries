#include "State.hpp"

jpl::_security::_cypher::_symmetric::State::State(const jpl::_security::_cypher::_symmetric::AES_TYPE* aes_type) : aes_type(aes_type){

    if(aes_type == nullptr){
        jpl::_security::_cypher::_error_cypher_jpl = CYPHER_JPL_AES_TYPE_NULLPTR;
    }

    if( jpl::_security::_cypher::checkError() ){
        this->cols = this->aes_type->getLength()/32;
        this->instanceState();
    }
}

void jpl::_security::_cypher::_symmetric::State::instanceState(){

    this->state = new const char*[4];
    for(unsigned short i = 0; i < 4; i++)
        this->state[i] = new char[this->cols];
}

jpl::_security::_cypher::_symmetric::State::~State(){

    for(unsigned short i = 0; i < 4; i++){
        delete[] this->state[i];
    }
}