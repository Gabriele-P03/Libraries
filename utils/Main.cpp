#include "src/FilesUtils.hpp"

int main(){

    std::fstream* file = new std::fstream;
    jpl::_utils::_files::getLocalFile("prova.txt", std::ios::in, &file);

    return 0;
}