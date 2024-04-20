/**
 * Json Object abstraction
 * 
 *
 * @file JSONObject.hpp
 * @author Gabriele-P03
 */

#ifndef JSON_OBJECT_JPL
#define JSON_OBJECT_JPL

#include <string>
#include <jpl/utils/structure/list/LinkedList.hpp>

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONArray;

            class JSONObject{
                
                protected:
                    unsigned long tabs; //Count how many tabs 
                    std::string name;

                    _utils::_collections::_list::LinkedList<JSONObject*> jsonObjects; //Children json object
                    _utils::_collections::_list::LinkedList<JSONArray*> jsonArray; //Children json object
            };
        }
    }
}

#endif