#include "src/structure/list/LinkedList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;

int main(){

    LinkedList<int> ll = LinkedList<int>();

    ll.add(0, 1);
    ll.add(0, 2);
    ll.add(0, 3);
    ll.add(0, 4);
    ll.add(0, 5);
    ll.add(0, 6);
    ll.add(0, 7);
    ll.add(0, 8);
    ll.add(0, 9);
    ll.add(0, 10);
    std::cout<<ll<<std::endl;

    return 0;
}