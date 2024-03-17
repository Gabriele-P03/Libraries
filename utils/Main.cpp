#include "src/debug/Profiler.hpp"
#include "src/StringUtils.hpp"

using namespace jpl;
using namespace _utils;

#include <iostream>
#include <chrono>
#include <thread>

int main(){
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    try{
        jpl::_utils::_profiler::Profiler profiler;
        profiler.start(1000);
        for(int i = 0; i < 10000; i++)
        {
            std::cout<<i<<" ";
        }
        profiler.end();
        for(int i = 0; i < profiler.getSystemInfoList()->size(); i++){
            std::cout<<*profiler.getSystemInfoList()->at(i);
        }
    }catch(const jpl::_exception::RuntimeException* ex){
        std::cout<<*ex;
    }
    //std::cout<<memInfo->totalMemory;
}