#include "src/structure/list/LinkedList.hpp"

#include <memory>

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list; 

class Bar{

    public:
        int* h;
        Bar(){
            h = new int(1);
        }
        ~Bar(){
            delete this->h;
        }

};

int main(){
        /*int *x = new int(1), *y = new int(2);
        LinkedList<int*>* list1 = new LinkedList<int*>{x, y};
        list1->addAll(list1);
        std::cout<<*list1<<std::endl;
        list1->remove(x);
        std::cout<<*list1;
        LinkedList<Bar*>* list1 = new LinkedList<Bar*>{new Bar(), new Bar()};
        //list1->addAll(list1);
        std::cout<<*list1<<std::endl;
        list1->clear();
        std::cout<<*list1;*/

        Bar* bar = new Bar();
        std::shared_ptr<Bar> ptr = std::make_shared<Bar>(*bar);
        std::cout<<ptr.use_count()<<std::endl;
        ptr.reset();
        std::cout<<ptr.use_count();
}