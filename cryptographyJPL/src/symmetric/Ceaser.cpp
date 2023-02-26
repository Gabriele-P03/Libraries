#include "Ceaser.hpp"

jpl::_cypher::_symmetric::Ceaser::Ceaser(unsigned int key){
    if(key >= MAX_KEY_CYPHER_JPL){
        jpl::print("Ceaser Cypher Error Occurred");
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_KEY_ERROR;
    }
                        
    this->key = key;
}