/**
 * This is meant to be an interface which can be used to sign a class which can be instanced by a json element.
 * Your class should have a default constructor and then one of these declared functions, which must be overriden
 * in your class, have to be called passing the json element 
 * 
 * @file JsonInection.hpp
 * @author Gabriele-P03
 * @date 25-09-2024
 */

#include "../JSONObject.hpp"

namespace jpl{
  namespace _parser{
    namespace _json{

        template <typename T>
        class JSONInjection {

            protected:
            
              virtual T* fromJSON(const JSONElement* element) = 0;
              virtual jpl::_utils::_collections::List<T*>* nFromJSON(const JSONArray* jsonArray) = 0;
        };
    }
  }  
} 

