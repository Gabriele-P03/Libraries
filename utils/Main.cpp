#include "src/structure/list/LinkedList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list; 

/*

    try{
        int *x = new int(1), *y = new int(2);
        LinkedList<int*>* list1 = new LinkedList<int*>{x, y};
        list1->addAll(list1);
        std::cout<<*list1<<std::endl;
        list1->clear();
        std::cout<<*list1;
        
    }catch(const _exception::RuntimeException* ex){
        std::cout<<ex->what();
    }
*/


int main(){

    int* x = new int(1);
    int* z = new int;
    memcpy(z, x, sizeof(int));
    
    delete z;
    delete x;
    std::cout<<"End"; 
}