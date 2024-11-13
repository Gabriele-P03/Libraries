/**
 * @file
 * 
 * DTD Attribute representation
 * 
 * Since the attribute must follow certain condition due to available values, here you are some exception that could be thrown  
 * 
 * ATTR_TYPE = LIST_CHOICE:
 *      1) If values is nullptr
 *      2) If value is not empty string but values does not contain it
 * 
 * ATTR_VALUE = FIXED
 *      1) If value is empty string
 * 
 * @author Gabriele-P03 
 */

#ifndef ATTRIBUTE_DTD_JPL
#define ATTRIBUTE_DTD_JPL

#include "Enums.hpp"
#define DEL_EFF_DS_JPL
#include <jpl/utils/structure/list/LinkedList.hpp>
#undef DEL_EFF_DS_JPL
#include <jpl/exception/runtime/IllegalStateException.hpp>

namespace jpl{
    namespace _parser{
        namespace _dtd{
            
            class Attribute{

                private:
                    const std::string name;
                    const ATTR_TYPE attr_type;
                    const ATTR_VALUE attr_value;
                    const std::string value;
                    const _utils::_collections::_list::LinkedList<std::string>* values;

                public:

                    Attribute(
                        const std::string &name, 
                        const ATTR_TYPE& attr_type,
                        const ATTR_VALUE& attr_value,
                        const std::string& value,
                        const _utils::_collections::_list::LinkedList<std::string>* values);

                    Attribute(const Attribute &attribute);

                    inline const std::string getName() const noexcept{return this->name;}
                    inline const ATTR_TYPE getAttrType() const noexcept{return this->attr_type;}
                    inline const ATTR_VALUE getAttrValue() const noexcept{return this->attr_value;}
                    inline const std::string getValue() const noexcept{return this->value;}

                    /**
                     * @return if this attribute has a list of value
                     */
                    inline bool hasList() const noexcept{return this->attr_type == ATTR_TYPE::LIST_CHOICE;} 

                    /**
                     * @throw IllegalStateException if this attribute does not contain a values list ( check it via bool hasList() )
                     * @return a const reference to the current attribute's values list
                     */
                    const _utils::_collections::_list::LinkedList<std::string>* getValues() const{
                        if(!this->hasList()){
                            throw _exception::IllegalStateException(this->name + " attribute does not have a values list");
                        }
                        return const_cast<const _utils::_collections::_list::LinkedList<std::string>*>(this->values);
                    }

                    ~Attribute();
            };
        }
    }
}

#endif