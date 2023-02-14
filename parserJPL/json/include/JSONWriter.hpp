/**
 * 
 * @file JSONWriter.hpp
 * @author Gabriele-P03 (pacegabriele@libero.it)
 * 
 * @brief Inline non-member functions for writing on JSON file
 * If you choose to use write(std::string*, std::fstream* &), then
 * you should add at the begin and at the end of the string respectively
 * open and close square/curly bracket in order to avoid syntax-errors.
 * This is already done by the relative functions
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

namespace JSON{

    inline void write(std::string* jsonAsString, std::fstream* &file){
        file->write(jsonAsString->c_str(), jsonAsString->size());
        file->flush();
    }

    inline void write(JSONObject* object, std::fstream* &file){
        write(new std::string("{" + *object->to_string() + "}"), file);
    }

    inline void write(JSONArray* array, std::fstream* &file){
        write(new std::string("[" + *array->to_string() + "]"), file);
    }
}