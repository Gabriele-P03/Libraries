#include "src/structure/list/ArrayList.hpp"

int main(){


    jpl::_utils::_collections::_list::ArrayList<int> list;

    list.add(1);
    list.add(5);
    list.add(6);

    std::cout<<list;

    jpl::_utils::_collections::_list::ArrayList<int> list1{
        1, 2, 3
    };

    return 0;
}