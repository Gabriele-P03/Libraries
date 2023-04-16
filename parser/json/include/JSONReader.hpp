/**
 * @file JSONReader.hpp
 * @author Gabriele-P03 (pacegabriele@libero.it)
 * 
 * @brief read functions return a pointer to string which represents the read 
 * json file, but they do not parse it as JSONObject, JSONArray and JSONMap.
 * It is done by parse(std::string jsonAsString).
 * 
 * This last function returns an std::variant depending on what is the root element of
 * json file (either JSONArray or JSONObject). Therefore you should be careful about
 * getting the right object via std::get.
 * It is already done by getJSONObject and getJSONArray. About them, I wish you're sure
 * what you're lookin' for before calling them - you could catch exception.  
 * 
 * @version 0.1
 * @date 2022-07-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <boost/algorithm/string/replace.hpp>
#include "JSONObject.hpp"
#include "JSONArray.hpp"

#include <jpl/logger/PrintLogger.hpp>

namespace JSON{

    typedef unsigned int READ_ERROR;

    const READ_ERROR EMPTY_STRING = 1;
    const READ_ERROR STRANGE_CHAR_IN_STRING = 2;

  
    /**
     * Read all json file as a single string 
     * 
     * @param path 
     * @return string* 
     */
    std::string* read(std::string path);

    /**
     * Read all json file as a single string  
     * 
     * @param file 
     * @return string* 
     */
    std::string* read(std::fstream* &file);


    std::variant<JSON::JSONObject*, JSON::JSONArray*, READ_ERROR> parse(std::string jsonAsString);

    /**
     * @param jsonAsString returned by file reading
     * @return the json object read by the string 
     */
    JSONObject* getJSONObject(std::string jsonAsString);

    /**
     * @param jsonAsString returned by file reading
     * @return the json array read by the string 
     */
    JSONArray* getJSONArray(std::string jsonAsString);
}