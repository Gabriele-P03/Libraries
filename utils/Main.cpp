#include "src/structure/list/ArrayList.hpp"

int main(){

    jpl::_utils::_collections::_list::ArrayList<int*> p_list{
        new int(1), new int(2), new int(3), new int(4), new int(5), new int(6), new int(7), new int(8), new int(9), new int(10)
    };
    jpl::_utils::_collections::_list::ArrayList<int> list{1,2,3,4,5,6,7,8,9,10};

    return 0;
}