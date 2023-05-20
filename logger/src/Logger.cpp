#include "Logger.hpp"

void jpl::_logger::Logger::print(std::string msg){

    this->print(msg, jpl::_logger::INFO);
}

void jpl::_logger::Logger::print(std::string msg, jpl::_logger::LOG_STATUS status){

    msg = "[ " + this->getFileNameOfInstance() + " -> " + status + " ]: " + msg + "\n";
    this->file->write(msg.c_str(), msg.size());
    this->file->flush();

    std::cout<<msg;
}

void jpl::_logger::Logger::closeLogger(){

    this->print("Logger closed");
    this->file->close();
}

jpl::_logger::Logger::~Logger(){
    //Include Exception and call IllegalState Logger has not been closed, then delete this instance
}

std::string jpl::_logger::Logger::getFileNameOfInstance(){

    std::tm *ltm = jpl::_logger::Logger::getTM();

    return  std::to_string((*ltm).tm_mday) + "-" + 
            std::to_string((*ltm).tm_mon+1) + "-" + 
            std::to_string((*ltm).tm_year + 1900) + "_" +
            std::to_string((*ltm).tm_hour) + "-" +
            std::to_string((*ltm).tm_min) + "-" +
            std::to_string((*ltm).tm_sec);
}