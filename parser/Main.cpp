#include "src/dtd/DTDUtils.hpp"
#include <jpl/utils/FilesUtils.hpp>

using namespace jpl;
using namespace _utils;
using namespace _parser;
using namespace _collections;
using namespace _list;

int main(){

    
    std::ifstream in("/home/gabriele/JPL/parser/out/linux/test.dtd");
    if(!in.is_open())
        exit(-1);
    const _dtd::DTD* dtd = _dtd::parse(in);
    delete dtd;
}


