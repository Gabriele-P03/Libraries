#include "src/structure/list/ArrayList.hpp"

int main(){


    jpl::_utils::_collections::_list::ArrayList<int> list{1,2,3,4,5,6,7,8,9,10};
    jpl::_utils::_collections::_list::ArrayList<int> list1(&list);

    std::cout<<list<<std::endl;
    list.removeAll(&list1);
    std::cout<<list<<std::endl<<std::endl<<list1;
    return 0;
}