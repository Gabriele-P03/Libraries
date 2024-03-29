#define DEL_EFF_DS_JPL
#include "src/structure/list/LinkedList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list; 


int main(){

    int*x = new int(1), *y = new int(2), *z = new int(3), *a = new int(4);
    LinkedList<int*>* list = new LinkedList<int*>{x,y,z,a};
    //std::cout<<*list<<std::endl;
    list->addAll(list);
    //std::cout<<*list<<std::endl;
    list->removeAll(list);
    //std::cout<<*list<<std::endl;
}