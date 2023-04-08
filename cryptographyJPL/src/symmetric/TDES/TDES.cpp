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


//CBC part
std::string* jpl::_cypher::_symmetric::TDES::cbc_encrypt(std::string plain_text){
    if(!this->iv_initialized){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_IV_UNIN_ERROR;
    }

    if(!jpl::_cypher::checkError()){
        return nullptr;
    }
    /*
     *  TDES-CBC works on single sub_blocks  
     * 
     */
    std::string* cyphered = new std::string("");
    bool* round_v = new bool[64];
    memcpy(round_v, this->IV, 64);
    do{
        unsigned long current_size = plain_text.size();
        std::string sub_block = plain_text.substr(0, current_size > 7 ? 8 : current_size);
        plain_text.erase(0, sub_block.size());
        if(sub_block.size() < 8){
            sub_block += std::string(8 - sub_block.size(), (char)5);
        }

        //Execute the xor-bits between IV and current sub_block
        const char* cc_sub_block = sub_block.c_str();
        bool* cc_sub_block_bits = jpl::_utils::cc_bits(cc_sub_block, 8);
        bool* cc_sub_block_bits_ived = jpl::_utils::_xor_bits(cc_sub_block_bits, round_v, 64);
        const char* cc_sub_block_ived = jpl::_utils::bits_cc(cc_sub_block_bits_ived, 64);
        delete[] cc_sub_block_bits;
        delete[] cc_sub_block_bits_ived;
        std::string* sub_block_ived = new std::string(cc_sub_block_ived, 8);
        std::string* buffer = this->ecb_encrypt(*sub_block_ived);
        delete sub_block_ived;

        //Let sub_block_ived become the next round_v
        delete[] round_v;
        round_v = jpl::_utils::cc_bits(buffer->c_str(), 8);
        cyphered->append(*buffer); 
        delete buffer;

    }while(!plain_text.empty());

    delete[] round_v;
    return cyphered;
}

std::string* jpl::_cypher::_symmetric::TDES::cbc_decrypt(std::string cyphered_text){
    if(!this->iv_initialized){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_IV_UNIN_ERROR;
    }

    if(!jpl::_cypher::checkError()){
        return nullptr;
    }
    /*
     *  TDES-CBC works on single sub_blocks  
     * 
     */
    std::string* cleared = new std::string("");
    bool* round_v = new bool[64];
    memcpy(round_v, this->IV, 64);
    do{
        std::string sub_block = cyphered_text.substr(0, 8);
        cyphered_text.erase(0, 8);

        //Execute the decryption of the current sub_block
        std::string* buffer = this->ecb_decrypt(sub_block);
        //Now let's do the xor between the buffer and the round_v
        bool*  buffer_bits = jpl::_utils::cc_bits(buffer->c_str(), 8);
        delete buffer;
        bool* buffer_bits_ived = jpl::_utils::_xor_bits(round_v, buffer_bits, 64);
        delete[] buffer_bits;
        const char* cc_buffer_ived = jpl::_utils::bits_cc(buffer_bits_ived, 64);
        delete[] buffer_bits_ived;
        std::string* buffer_ived = new std::string(cc_buffer_ived, 8);

        //Let sub_block_ived become the next round_v
        delete[] round_v;
        round_v = jpl::_utils::cc_bits(sub_block.c_str(), 8);
        cleared->append(*buffer_ived); 
        delete buffer_ived;

    }while(!cyphered_text.empty());

    delete[] round_v;
    return cleared;
}


void jpl::_cypher::_symmetric::TDES::set_CBC_IV(std::string IV){
    this->IV = jpl::_utils::cc_bits(IV.c_str(), 8);
    this->iv_initialized = true;
}

jpl::_cypher::_symmetric::TDES::~TDES(){

    if(this->iv_initialized)
        delete[] this->IV;

    delete first;
    delete second;
    delete third;
}

