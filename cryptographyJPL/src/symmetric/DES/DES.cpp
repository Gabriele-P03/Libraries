#include "DES.hpp"

jpl::_cypher::_symmetric::DES::DES(std::string key){
    
    this->raw_key = key.c_str();
    this->iv_initialized = false;

    if(key.size() != DES_JPL_RAW_KEY_SIZE/8){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_KEY_SIZE_ERROR;
    }else{
        this->_pc1();
    }      
}

int jpl::_cypher::_symmetric::DES::_pc1(){

    /*
        Since DES works with bits and not with chars,
        for convenience, it transforms bits in boolean value
    */
    bool *bits_raw_key = jpl::_utils::cc_bits(this->raw_key, DES_JPL_RAW_KEY_SIZE/8);

    //Execution of the PC1
    bool* pc1_buffer = new bool[DES_JPL_PC1_KEY_SIZE];
    for (unsigned int i = 0; i < DES_JPL_PC1_KEY_SIZE; i++){
        // Retrieve the indices
        unsigned short index = jpl::_cypher::_symmetric::_des::pc1_matrix[i];
        pc1_buffer[i] = bits_raw_key[index-1];
    }

    delete[] bits_raw_key;

    //Splitting into left-hand and right one
    bool *pc1_buffer_l = new bool[DES_JPL_PC1_KEY_SIZE/2], *pc1_buffer_r = new bool[DES_JPL_PC1_KEY_SIZE/2];
    memcpy(pc1_buffer_l, pc1_buffer, 28);
    memcpy(pc1_buffer_r, &pc1_buffer[28], 28);
    delete[] pc1_buffer;


    //Now let's execute the shifting and pc2
    for(unsigned short i = 0; i < DES_JPL_ROUND; i++){

        this->rotate(pc1_buffer_l, pc1_buffer_r, i+1);

        this->_pc2(pc1_buffer_l, pc1_buffer_r, i);
    }

    delete[] pc1_buffer_l;
    delete[] pc1_buffer_r;

    return 0;
}

void jpl::_cypher::_symmetric::DES::rotate(bool *&_l, bool *&_r, unsigned short round){

    if (round == 1 || round == 2 || round == 9 || round == 16){
        //Shifting 1
        bool first_l = _l[0], first_r = _r[0];
        for(unsigned short i = 0; i < DES_JPL_PC1_KEY_SIZE/2 - 1; i++){
            _l[i] = _l[i+1];
            _r[i] = _r[i+1];
        }
        _l[DES_JPL_PC1_KEY_SIZE/2-1] = first_l;
        _r[DES_JPL_PC1_KEY_SIZE/2-1] = first_r;
    }else{
        //Shifting 2 
        bool first_l = _l[0], first_r = _r[0], second_l = _l[1], second_r = _r[1];
        for(unsigned short i = 0; i < DES_JPL_PC1_KEY_SIZE/2-2; i++){
            _l[i] = _l[i+2];
            _r[i] = _r[i+2];
        }
        _l[DES_JPL_PC1_KEY_SIZE/2-2] = first_l;
        _r[DES_JPL_PC1_KEY_SIZE/2-2] = first_r;
        _l[DES_JPL_PC1_KEY_SIZE/2-1] = second_l;
        _r[DES_JPL_PC1_KEY_SIZE/2-1] = second_r;
    }
}

void jpl::_cypher::_symmetric::DES::_pc2(bool *_l, bool *_r, unsigned short round)
{
    bool* _l_r = new bool[56];
    memcpy(_l_r, _l, 28);
    memcpy(&_l_r[28], _r, 28);
    bool *buffer = new bool[DES_JPL_PC2_KEY_SIZE];

    for (unsigned short i = 0; i < DES_JPL_PC2_KEY_SIZE; i++){
        unsigned short index = jpl::_cypher::_symmetric::_des::pc2_matrix[i];
        buffer[i] = _l_r[index-1];
    }
    this->sub_keys_bits.push_back(buffer);
}

bool* jpl::_cypher::_symmetric::DES::mangler(bool* buffer, unsigned short round){

    //Get the round key
    bool* key_round = this->sub_keys_bits.at(round);

    //Execute the expansion matrix
    bool* buffer_exped = new bool[48];
    for(unsigned short i = 0; i < 48; i++){
        unsigned short index = jpl::_cypher::_symmetric::_des::exp_matrix[i];
        buffer_exped[i] = buffer[index-1];
    }

    bool* bits_xor = jpl::_utils::_xor_bits(buffer_exped, key_round, 48);
    delete[] buffer_exped;

    //Execute S boxes
    bool *post_p = new bool[32], *pre_p = new bool[32];;
    for(unsigned short i = 0; i < 8; i++){
        const unsigned short* box = jpl::_cypher::_symmetric::_des::s_boxes[i];
        //Let's calculte row and col

        //Row is the external bits
        unsigned short row = ( (bits_xor[6*i] << 1) | bits_xor[6*i + 5] );
        unsigned short col = bits_xor[6*i + 1];
        col = col << 1;
        col |= bits_xor[6*i + 2];
        col = col << 1;
        col |= bits_xor[6*i + 3];
        col = col << 1;
        col |= bits_xor[6*i + 4];
        //retrieve the element at row-col
        unsigned short element = box[row*16 + col];
        //Transform it as 4 bits
        pre_p[4*i] = (( (element >> 3) & 0x01) == 0x01);
        pre_p[4*i + 1] = (( (element >> 2) & 0x01) == 0x01);
        pre_p[4*i + 2] = (( (element >> 1) & 0x01) == 0x01);
        pre_p[4*i + 3] = ((element & 0x01) == 0x01);
    }

    //Let's execute permutation
    for(unsigned short j = 0; j < 32; j++){
        unsigned short index = jpl::_cypher::_symmetric::_des::p_matrix[j];
        post_p[j] = pre_p[index-1];
    }
    delete[] pre_p;

    return post_p;
}

std::string* jpl::_cypher::_symmetric::DES::ecb_encrypt(std::string plain_text){
    if(!jpl::_cypher::checkError()){
        return nullptr;
    }
    std::string* cyphered = new std::string("");
    //plain_text must be cyphered 64 bits by 64 (it means 8 bytes)
    do{

        unsigned long current_size = plain_text.size();
        std::string plain_block = plain_text.substr(0, current_size > 7 ? 8 : current_size);
        plain_text.erase(0, plain_block.size());
        //Check if padding is required
        if(current_size < 7){
            plain_block += std::string(8 - current_size, (char)5);
        }

        //let's convert bytes into bits
        bool* plain_block_bits = jpl::_utils::cc_bits(plain_block.c_str(), 8);
        //Let's encrypt the sub block
        bool* cyphered_bits = this->enc_sub_block(plain_block_bits);

        const char* bits_cc_ = jpl::_utils::bits_cc(cyphered_bits, 64);
        cyphered->append( std::string(bits_cc_, 8) );

        delete[] bits_cc_;
        delete[] cyphered_bits;
        delete[] plain_block_bits;
        
    }while( !(plain_text.empty()) );

    return cyphered;
}

bool* jpl::_cypher::_symmetric::DES::enc_sub_block(bool* plain_block_bits){
        //let's execute the initial permutation on the plain block
        bool* ip_buffer = new bool[64];
        for(unsigned short i = 0; i < 64; i++){
            ip_buffer[i] = plain_block_bits[jpl::_cypher::_symmetric::_des::ip_matrix[i]-1];
        }
        //Let's split it into left and right one
        bool* buffer_l = new bool[32], *buffer_r = new bool[32];
        memcpy((void*)buffer_l, (void*)ip_buffer, 32);
        memcpy((void*)buffer_r, (void*)&ip_buffer[32], 32);

        bool* _left = buffer_l, *_right = buffer_r;
        for(unsigned short i = 0; i < DES_JPL_ROUND; i++){

            bool* manglered = this->mangler(_right, i);
            bool* bits_xored = jpl::_utils::_xor_bits(_left, manglered, 32);

            delete[] _left;
            delete[] manglered;
            _left = _right;
            _right = bits_xored;
        }

        bool* pre_fp = new bool[64];
        memcpy((void*)pre_fp, (void*)_right, 32);
        memcpy((void*)&pre_fp[32], (void*)_left, 32);

        delete[] buffer_r;
        delete[] ip_buffer;

        //Execute the last permutation
        bool* post_fp = new bool[64];
        for(unsigned short i = 0; i < 64; i++){
            unsigned short index = jpl::_cypher::_symmetric::_des::fp_matrix[i];
            post_fp[i] = pre_fp[index-1];
        }
        delete[] pre_fp;

        return post_fp;
}

std::string* jpl::_cypher::_symmetric::DES::ecb_decrypt(std::string cyphered_text){
    if(!jpl::_cypher::checkError()){
        return nullptr;
    }
    //Reverse keys
    for(unsigned short i = 0; i < 8; i++){
        bool* tmp = this->sub_keys_bits.at(i);
        this->sub_keys_bits.at(i) = this->sub_keys_bits.at(15-i);
        this->sub_keys_bits.at(15-i) = tmp; 
    }

    std::string *plain_text = this->ecb_encrypt(cyphered_text);

    //Re-ordering keys
    for(unsigned short i = 0; i < 8; i++){
        bool* tmp = this->sub_keys_bits.at(i);
        this->sub_keys_bits.at(i) = this->sub_keys_bits.at(15-i);
        this->sub_keys_bits.at(15-i) = tmp; 
    }

    return plain_text;
}

void jpl::_cypher::_symmetric::DES::set_CBC_IV(std::string IV){

    if(!jpl::_cypher::checkError()){
        return;
    }

    if(IV.size() != 8){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_IV_SIZE_ERROR;
    }else{
        this->iv_initialized = true;
        this->IV = jpl::_utils::cc_bits(IV.c_str(), 8);
    }
}

std::string* jpl::_cypher::_symmetric::DES::cbc_encrypt(std::string plain_text){

    if(!this->iv_initialized){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_IV_UNIN_ERROR;
    }

    if(!jpl::_cypher::checkError()){
        return nullptr;
    }
    
    std::string* cyphered = new std::string("");
    //plain_text must be cyphered 64 bits by 64 (it means 8 bytes)

    bool* round_v = new bool[64];
    memcpy((void*)round_v, (void*)this->IV, 64);
    do{

        unsigned long current_size = plain_text.size();
        std::string plain_block = plain_text.substr(0, current_size > 7 ? 8 : current_size);
        plain_text.erase(0, plain_block.size());
        //Check if padding is required
        if(current_size < 7){
            plain_block += std::string(8 - current_size, (char)5);
        }

        //let's convert bytes into bits
        bool* plain_block_bits = jpl::_utils::cc_bits(plain_block.c_str(), 8);
        //Let's encrypt the sub block
        bool* plain_block_bits_ived = jpl::_utils::_xor_bits(plain_block_bits, round_v, 64);
        bool* cyphered_bits = this->enc_sub_block(plain_block_bits_ived);

        char* buffer = jpl::_utils::bits_cc(cyphered_bits, 64);
        cyphered->append( std::string(buffer, 8) );

        delete[] buffer;
        delete[] round_v;
        round_v = cyphered_bits;
        delete[] plain_block_bits_ived;
        delete[] plain_block_bits;
        
    }while( !(plain_text.empty()) );

    delete[] round_v;
    return cyphered;
}

std::string* jpl::_cypher::_symmetric::DES::cbc_decrypt(std::string cyphered_text){
    
    if(!this->iv_initialized){
        jpl::_cypher::_error_cypher_jpl = CYPHER_JPL_IV_UNIN_ERROR;
    }
    if(!jpl::_cypher::checkError()){
        return nullptr;
    }

    //Inverting keys
    for(unsigned short i = 0; i < 8; i++){
        bool* tmp = this->sub_keys_bits.at(i);
        this->sub_keys_bits.at(i) = this->sub_keys_bits.at(15-i);
        this->sub_keys_bits.at(15-i) = tmp; 
    }

    std::string* plained_text = new std::string("");

    bool *current_iv = new bool[64];
    memcpy(current_iv, this->IV, 64);
    do{

        const char* current_block = cyphered_text.substr(0, 8).c_str();
        cyphered_text.erase(0, 8);
        bool* current_block_bits = jpl::_utils::cc_bits(current_block, 8);
        bool* enc_sub_block_ = this->enc_sub_block(current_block_bits);
        bool* enc_sub_block_ived = jpl::_utils::_xor_bits(enc_sub_block_, current_iv, 64);

        const char* bits_cc_ = jpl::_utils::bits_cc(enc_sub_block_ived, 64);
        plained_text->append( std::string(bits_cc_, 8) );

        delete[] current_iv;
        current_iv = current_block_bits;

        delete[] enc_sub_block_;
        delete[] enc_sub_block_ived;
        delete[] bits_cc_;

    }while( !(cyphered_text.empty()) );

    //Re-ordering keys
    for(unsigned short i = 0; i < 8; i++){
        bool* tmp = this->sub_keys_bits.at(i);
        this->sub_keys_bits.at(i) = this->sub_keys_bits.at(15-i);
        this->sub_keys_bits.at(15-i) = tmp; 
    }

    delete[] current_iv;
    return plained_text;
}

jpl::_cypher::_symmetric::DES::~DES(){

    if(this->iv_initialized){
        delete[] IV;
    }
    delete[] this->raw_key;
}