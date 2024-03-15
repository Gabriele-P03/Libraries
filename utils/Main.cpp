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
        
        while(true){
            const jpl::_utils::_profiler::SystemInfo* sysInfo = profiler.measure(); 
            std::cout<<*sysInfo;
        }
    }catch(const jpl::_exception::RuntimeException* ex){
        std::cout<<*ex;
    }
    //std::cout<<memInfo->totalMemory;
}