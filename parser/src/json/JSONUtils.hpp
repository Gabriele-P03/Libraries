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
#include <jpl/utils/StringUtils.hpp>
#include "exception/JSONParseException.hpp"

namespace jpl{
    namespace _parser{
        namespace _json{

            const std::regex stct_regex = std::regex("^[\\[\\]\\{}\"].*");

            JSONElement* parseJSONString(std::string &buffer, bool parseName, size_t tabs);

            JSONObject* parseJSONObjectByString(std::string &buffer, bool parseName = true, size_t tabs = 0);
            JSONArray* parseJSONArrayByString(std::string &buffer, bool parseName = true, size_t tabs = 0);
            JSONField* parseJSONFieldByString(std::string &buffer, bool parseName = true, size_t tabs = 0);
        
            /**
             * substring, trim, remove comma and trim
            */
            void stct(std::string &buffer, size_t i);
        }
    }
}

#endif