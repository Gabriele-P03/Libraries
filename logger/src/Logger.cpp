#include "Logger.hpp"

#ifndef CUSTOM_LOGGER_JPL
    jpl::_logger::Logger* jpl::_logger::Logger::INSTANCE = new jpl::_logger::Logger(
        jpl::_utils::_files::getLocalPath("/logs/" + jpl::_logger::Logger::getFileNameOfInstance() + ".txt")
    );
#endif


jpl::_logger::LOG_STATUS jpl::_logger::INFO = "INF";
jpl::_logger::LOG_STATUS jpl::_logger::WARNING = "WAR";
jpl::_logger::LOG_STATUS jpl::_logger::ERROR = "ERR";
jpl::_logger::LOG_STATUS jpl::_logger::DEBUG = "DBG";

void jpl::_logger::Logger::print(std::string msg){

    this->print(msg, jpl::_logger::INFO);
}

void jpl::_logger::Logger::print(std::string msg, jpl::_logger::LOG_STATUS status){

    msg = "[" + this->getFileNameOfInstance() + " -> " + status + "]: " + msg + "\n";
    std::cout<<msg;
    if(flag){
        this->file->write(msg.c_str(), msg.size());
        this->file->flush();
    }
}

void jpl::_logger::Logger::closeLogger(){
    //In order to write on the file even when logger is closed, flag is set to false after this operation
    this->print("Closing Logger...");
    this->file->close();
    this->flag = false;
}

std::string jpl::_logger::Logger::getFileNameOfInstance(){

    std::tm *ltm = jpl::_logger::Logger::getTM();

    return  std::to_string((*ltm).tm_mday) + "-" + 
            std::to_string((*ltm).tm_mon+1) + "-" + 
            std::to_string((*ltm).tm_year + 1900) + "_" +
            std::to_string((*ltm).tm_hour) + ":" +
            std::to_string((*ltm).tm_min) + ":" +
            std::to_string((*ltm).tm_sec);
}