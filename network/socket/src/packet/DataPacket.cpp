#include "DataPacket.hpp"


void jpl::_network::_packet::to_cstr(jpl::_network::_packet::DataPacket* packet, const char* &buffer, std::size_t &size){

    size = packet->getLength() + FLAG_SIZE;
    buffer = new char[size];

    #ifdef PARSE_FLAGS_PACKET_JPL
        char tmp = packet->getFlags();
        memcpy((void*)&buffer[0], &tmp, FLAG_SIZE);
    #endif

    memcpy( (void*)&buffer[1], packet->getData(), packet->getLength());
}

#ifdef PARSE_FLAGS_PACKET_JPL

    const char jpl::_network::_packet::DataPacket::getFlags(){
        return this->flags;
    }

    bool jpl::_network::_packet::DataPacket::isRoot(){
        return this->flags & ROOT_FLAG;
    }

    bool jpl::_network::_packet::DataPacket::isEcho(){
        return this->flags & ECHO_FLAG;
    }

    bool jpl::_network::_packet::DataPacket::isJoin(){
        return this->flags & JOIN_FLAG;
    }

    bool jpl::_network::_packet::DataPacket::isQuit(){
        return this->flags & QUIT_FLAG;
    }

    bool jpl::_network::_packet::DataPacket::checkFlags(){

        if(this->isQuit() && this->isJoin())
            return false;

        //Check if it is a echo packet but flags contains other ones
        if(  (this->getFlags() & ECHO_FLAG) == ECHO_FLAG && this->getFlags() != ECHO_FLAG )
            return false;

        return true;
    }

#endif

jpl::_network::_packet::DataPacket::DataPacket(const char* data, std::size_t size){

    this->size_data = size - FLAG_SIZE;
    this->extract(data);
}

jpl::_network::_packet::DataPacket::DataPacket(const char flags, const char* data, std::size_t size){

    this->size_data = size;
    
    #ifdef PARSE_FLAGS_PACKET_JPL
        this->flags = flags;
    #endif
    this->data = new char[this->size_data];
    memcpy((void*)this->data, data, this->size_data);
}

jpl::_network::_packet::DataPacket::DataPacket(){

    #ifdef PARSE_FLAGS_PACKET_JPL
        this->flags = ECHO_FLAG;
    #endif
}

const char* jpl::_network::_packet::DataPacket::getData(){
    return this->data;
}

std::size_t jpl::_network::_packet::DataPacket::getLength(){
    return this->size_data;
}