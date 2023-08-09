#include "src/structure/list/ArrayList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list;

#include <iostream>

void print(ArrayList<int> list){

    for(unsigned int i = 0; i < list.getSize(); i++){
        std::cout<<*list.get(i)<<" ";
    }
    std::cout<<std::endl;
}

int main(){

    ArrayList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    print(list);

    list.add(1, 67);

    print(list); 

    return 0;
}