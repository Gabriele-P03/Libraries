#include "src/ConversionUtils.hpp"

#include <iostream>

int main(){

    const char* tmp = "1";
    bool* buffer = jpl::_utils::_conversions::cc_bits(tmp, 1);  
    tmp = jpl::_utils::_conversions::bits_cc(buffer, 8); 
}