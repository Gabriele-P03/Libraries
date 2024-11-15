/**
 * @file
 * 
 * This is the abstraction of a DTD Entity
 * 
 * If the value contains a URL/URI - and therefore it is an EXTERNAL ENTITY - entity_type is SYSTEM, otherwise it
 * is always INTERNAL
 * 
 * @author Gabriele-P03
 */

#ifndef ENTITY_DTD_JPL
#define ENTITY_DTD_JPL

#include <string>
#include <jpl/exception/runtime/IllegalArgumentException.hpp>

namespace jpl{
    namespace _parser{
        namespace _dtd{

            enum ENTITY_TYPE{
                INTERNAL,
                SYSTEM
            };

            class Entity{

                private:
                    const ENTITY_TYPE entity_type;
                    const std::string name;
                    const std::string value;    //It also contains URL when entity_type is SYSTEM

                public:
                    /**
                     * @param entity_type 
                     * @param name
                     * @param value with 
                     */
                    Entity(const ENTITY_TYPE entity_type, const std::string &name, const std::string value)
                        : entity_type(entity_type), name(name), value(value){
                        
                        if(this->name.empty()){
                            throw jpl::_exception::IllegalArgumentException("Entity name is empty");
                        }
                        if(this->value.empty()){
                            throw jpl::_exception::IllegalArgumentException("Entity value is empty");
                        }
                    }

                    const ENTITY_TYPE &getEntityType() const noexcept{
                        return this->entity_type;
                    }

                    const std::string &getName() const noexcept{return this->name;}
                    const std::string &getValue() const noexcept{return this->value;} 
            };
        }
    }
}

#endif