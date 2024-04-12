#define UFW_LOGGER_JPL
#include "src/LoggerWrapper.hpp"

int main(){

    jpl::_logger::print("Prova", jpl::_logger::INFO_JPL);

    //jpl::_logger::Logger::INSTANCE->closeLogger();

    return 0;
}