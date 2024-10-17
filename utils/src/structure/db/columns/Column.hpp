/**
 * @file
 * 
 * This header file contains concept about AbstractColumn specialization; if you are interested to
 * decleare (and define) your own, you should modify the sequence of std::__or_ and then define 
 * the getValue(Tuple) inside the source file
 * 
 * @author Gabriele-P03
 */

#ifndef COLUMN_JPL
#define COLUMN_JPL

#include "AbstractColumn.hpp"

namespace jpl{
    namespace _utils{
        namespace _collections{

            
            template <typename P>
            concept Primitive = std::__or_<std::is_integral<P>, std::is_same<P, std::string>>::value;

            template<typename Primitive>
            class Column : public AbstractColumn{

                private:
                    Primitive getValue(Tuple* tuple) const;
                    void setValue(Tuple* tuple, Primitive p) const;

                    friend class TableWrapper;
                
                public:
                    Column(std::string name, bool mandatory) : AbstractColumn(name, mandatory){}

            };
        }
    }
}

#endif