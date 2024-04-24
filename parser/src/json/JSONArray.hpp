/**
 * Json Array abstraction
 * 
 *
 * @file JSONObject.hpp
 * @author Gabriele-P03
 */

#ifndef JSON_ARRAY_JPL
#define JSON_ARRAY_JPL

#include <string>
#include <jpl/utils/structure/list/LinkedList.hpp>

namespace jpl{
    namespace _parser{
        namespace _json{

            class JSONObject;

            class JSONArray{
                
                protected:
                    unsigned long tabs; //Count how many tabs. They will be used for indentation 
                    std::string name;

                    _utils::_collections::_list::LinkedList<JSONObject*> jsonObjects;   //Children json object
                    _utils::_collections::_list::LinkedList<JSONArray*> jsonArray;      //Children json array
                    _utils::_collections::_list::LinkedList<JSONField*> fields;         //Children json field

                public:
                    JSONArray(std::string name, unsigned long tabs);
                    JSONArray(std::string name);
                    JSONArray();
            };
        }
    }
}

#endif