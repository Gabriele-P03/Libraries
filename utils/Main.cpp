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
        std::cout<<*profiler.measure();
        /*profiler.start(100);
        for(int i = 0; i < 1000000000; i++){
        }
        profiler.end();

        const std::vector<const jpl::_utils::_profiler::SystemInfo*>* vec = profiler.getSystemInfoList();
        for(int i = 0; i < vec->size(); i++){
            std::cout<<*vec->at(i);
        }*/
    }catch(const jpl::_exception::RuntimeException* ex){
        std::cout<<*ex;
    }
    //std::cout<<memInfo->totalMemory;
}