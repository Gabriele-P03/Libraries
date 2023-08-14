#include "src/structure/list/ArrayList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list;

#include <iostream>

template<typename T>
void print(ArrayList<T>* list){

    for(unsigned int i = 0; i < list->getSize(); i++){
        std::cout<<*list->get(i)<<" ";
    }
    std::cout<<std::endl;
}

int main(){

    ArrayList<unsigned long>* list = new ArrayList<unsigned long>();
    list->add(1);
    list->add(2);
    list->add(3);

    ArrayList<unsigned long>* list1 = list;

    print(list);

    list->removeAt(1);

    print(list);


    return 0;
}