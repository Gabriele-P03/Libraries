#include "src/structure/list/LinkedList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list;

int main(){

    LinkedList<int> ll = LinkedList<int>();

    ll.add(0, 1);
    ll.add(0, 2);
    ll.add(0, 3);
    ll.add(0, 4);
    ll.add(0, 5);

    LinkedList<int> ll1 = LinkedList<int>();
    ll1.add(0, 6);
    ll1.add(0, 7);
    ll1.add(0, 8);
    ll1.add(0, 9);
    ll1.add(0, 10);

    ll.addAll(&ll1);


    std::cout<<ll<<std::endl<<ll1<<std::endl;  
    ll.removeAll(&ll1);
    ll1.compress();
    std::cout<<std::endl<<ll<<std::endl<<ll1;

    return 0;
}