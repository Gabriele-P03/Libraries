
#define READ_FILE_JPL
#include "FilesUtils.hpp"

int main(){

    std::fstream* file;
    getLocalFile("path.json", std::ios_base::in, &file);
    
    return 0;
}