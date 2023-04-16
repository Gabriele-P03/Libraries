#pragma once

#include <vector>
#include <string>
#include "JSONObject.hpp"
#include "JSONMap.hpp"

namespace JSON{

    class JSONObject;

    class JSONArray{

        private:
        
            unsigned int size;

        public:

            std::string name;

            std::vector<JSONObject> objects;
            std::vector<JSONArray> arrays;
            std::vector<std::string> values;

            JSONArray(std::string arrayAsString);
            JSONArray(std::string arrayAsString, unsigned int offset);

            std::string* to_string();

            unsigned int getSize();

            JSONObject* getJSONObjectByName(std::string name);
            JSONArray* getJSONArrayByName(std::string name);
    };
}