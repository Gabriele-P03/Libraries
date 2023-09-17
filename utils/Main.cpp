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
    ll.add(2, 8);
    ll.add(5, 11);
    return 0;
}