/**
 * 
 * SPLIT FUNCTION
 * 
*/

#ifndef STRING_UTILS_JPL
#define STRING_UTILS_JPL

#include <string>
#include <vector>
#include <regex>

namespace jpl{
    namespace _utils{
        namespace _string{

            /**
             * @return Splitted src using regex
             * @param src
             * @param regex
             * @param maxSize max amount of splitted string to return
            */
            std::vector<std::string>* split(std::string src, std::regex regex, const unsigned long long maxSize);
            /**
             * @return Splitted src using regex
             * @param src
             * @param regex
            */
            std::vector<std::string>* split(std::string src, std::regex regex);
        }
    }
}

#endif