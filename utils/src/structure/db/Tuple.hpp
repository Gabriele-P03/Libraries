/**
 * @file
 * 
 * This implementation of Tuple is able to manage a dynamic run-time indexing in order to 
 * give you a certain freedom of usage. In order to improve performance, ArrayList is used in this impl.
 * 
 * Values' getters are available as public, instead Setter and Adder are available via Table (friend class)
 * since they need to check either if a new column may be added (Table is editable) or if tuple is editable
 * 
 * The field index is 0 only when the tuple is instanced outside from any table's context
 * 
 * A NULL value of a nullable column is represented by NULL 
 * 
 * Be carefull when managing index and either getter or setter since the field index represents the ID
 * of the tuple inside the database's table, instead the index argument of any functions represents the
 * position inside the list
 * 
 * @author Gabriele-P03
 */
#ifndef TUPLE_JPL
#define TUPLE_JPL

#include <cstdarg>
#include "../list/ArrayList.hpp"
#include <string>
#include <jpl/exception/runtime/IndexOutOfBoundsException.hpp>

namespace jpl{
    namespace _utils{
        namespace _collections{

            class Tuple{
                
                protected: 

                    /**
                     * Index of the tuple. It should be unique in a Table's context, therefore
                     * its value should be equals to index+1 of the position of this tuple into
                     * the table
                     */
                    size_t index;
                    _list::ArrayList<std::string>* values;

                    /**
                     * @param index
                     * @param value new value
                     * @throw IndexOutOfBound if index is greater or equal than values' size
                     */
                    void setValue(size_t index, std::string value){
                        if(index < this->values->getSize())
                            this->values->set(index, value);
                        else
                            this->values->add(index, value);
                    }


                public:
                    
                    template<typename> friend class Column;
                    friend class Table;
                    
                    /**
                     * @param index default 0
                     */
                    Tuple(size_t index = 0) : Tuple(index, new _list::ArrayList<std::string>()){}
                    /**
                     * @param index
                     * @param values 
                     */
                    Tuple(size_t index, _list::ArrayList<std::string>* values){
                        this->index = index;
                        this->values = values;
                    }

                    /**
                     * @param index 
                     * @return the value at index position
                     * @throw IndexOutOfBounds if index is greater or equals than values' size
                     */
                    std::string getValue(size_t index) const {
                        return this->values->get(index);    //getter method does already throw IOOB
                    }

                    /**
                     * @return index of this tuple
                     */
                    size_t getIndex() const noexcept {return this->index;}

                    ~Tuple(){
                        this->values->clear();
                        delete this->values;
                    }
            };
        }
    }
}

#endif