/**
 * @file In this header file there are some utility functions in order to read and parse - and 
 * vice-versa - json file 
 * 
 * 
 * @author Gabriele-P03
 * @date 27-04-2024
*/

#ifndef JSON_UTILS_JPL
#define JSON_UTILS_JPL

#include "JSONObject.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            /**
             * @param buffer which contains field as json string
             * @return JSONField parsed by given string
            */
            JSONField* parseFieldByString(std::string buffer);

            std::string* smartFieldDivide(std::string f);

        }
    }
}

#endif