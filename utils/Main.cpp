#include "Main.hpp"

using namespace jpl::_utils::_string;

int main(){

    std::string src = "{\"obj1\":{\"obj1_1\":}}{\"f\":false}}}}";
    std::cout<<src;
    size_t x = getIndexGroupOver(src, std::regex("\\{"), std::regex("\\}"));
    return 0;
}