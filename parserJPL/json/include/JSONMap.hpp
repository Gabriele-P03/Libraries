#pragma once

#include <string>

namespace JSON{

    class JSONMap{

        public:
            
            std::string key, value;

            JSONMap(std::string mapAsString);
            JSONMap(std::string key, std::string value);

            std::string* to_string();
    };
}