#pragma once

#include <vector>
#include <string>
#include "JSONArray.hpp"
#include "JSONMap.hpp"
#include <cmath>

namespace JSON{

    class JSONArray;

    class JSONObject{

        private:
            
            unsigned int size;

        public:

            std::string name;

            std::vector<JSONObject> objects;
            std::vector<JSONArray> arrays;
            std::vector<JSONMap> maps;

            JSONObject(std::string objectAsString);
            JSONObject(std::string objectAsString, unsigned int offset);

            std::string* to_string();

            unsigned int getSize();

            JSONObject* getJSONObjectByName(std::string name);
            JSONArray* getJSONArrayByName(std::string name);
            JSONMap* getJSONMapByKey(std::string name);
    };
}
