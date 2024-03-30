#define DEL_EFF_DS_JPL
#include "src/structure/list/LinkedList.hpp"

#include "src/structure/list/ArrayList.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;
using namespace _list; 

static int c = 0;

class Bar{

    public:
        int x;
        Bar(){
            this->x = ++c;
        }
        ~Bar(){
            std::cout<<"Deleting "<<x<<"...";
        }

        friend std::ostream& operator<<(std::ostream &os, const Bar &bar){
            os<<bar.x;
            return os;
        }
};

int main(){

    ArrayList<Bar*>* list = new ArrayList<Bar*>(10);
    Bar* bar = new Bar();
    list->add(bar);
    //list->clear();
    delete list;

    std::cout<<"Del";
}