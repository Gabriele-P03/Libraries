#include "src/Logger.hpp"

int main(){

    jpl::_logger::Logger::INSTANCE->print("Prova DBG", jpl::_logger::DEBUG);

    return 0;
}