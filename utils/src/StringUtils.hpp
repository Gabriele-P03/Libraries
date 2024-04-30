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
#include <algorithm>

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


            /**
             * @brief Trim the beginning of given std::string
             * @param src
             * @return src 
            */
            std::string startTrim(std::string src){
                std::string s = src;
                s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }));
                return s;
            }
            /**
             * @brief Trim the end of given std::string
             * @param src
             * @return src 
            */
            std::string endTrim(std::string src){
                std::string s = src; 
                s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }).base(), s.end());
                return s;
            }
            /**
             * @brief Trim the beginning and the end both of given std::string
             * @param src
             * @return src 
            */
            std::string trim(std::string src){
                return jpl::_utils::_string::startTrim(jpl::_utils::_string::endTrim(src));
            }


            /**
             * @param src the input string
             * @param regex the std::basic_regex which will be matched against src
             * @param fmt the string which will be inserted 
             * @param flags the match flags, default is std::regex_constants::format_first_only   
             * @return src modified based on regex and fmt 
            */
            std::string replace(std::string src, std::regex regex, std::string fmt, std::regex_constants::match_flag_type flags = std::regex_constants::format_first_only){
                return std::regex_replace(src, regex, fmt, flags);
            }
            /**
             * @param src the input string
             * @param regex the std::basic_regex which will be matched against src
             * @param fmt the string which will be inserted   
             * @param flags the match flags
             * @return src modified based on regex, fmt and flags 
            */
            std::string replaceAll(std::string src, std::regex regex, std::string fmt){
                return std::regex_replace(src, regex, fmt, std::regex_constants::match_any);
            }


            /**
             * @param src the input string
             * @param regex the regex which will be matched against src
             * @return how many times the regex has been matched against src
            */
            size_t count(std::string src, std::regex regex){
                auto beg = std::sregex_iterator(src.begin(), src.end(), regex);
                auto end = std::sregex_iterator();
                return std::distance(beg, end);
            }


            /**
             * @param src the input string
             * @return the given input string formatted as UPPER case
            */
            std::string toUpper(std::string src){
                std::string buffer;
                std::transform(src.begin(), src.end(), buffer.begin(), ::toupper);
                return buffer;
            }
            /**
             * @param src the input string
             * @return the given input string formatted as LOWER case
            */
            std::string toLower(std::string src){
                std::string buffer;
                std::transform(src.begin(), src.end(), buffer.begin(), ::tolower);
                return buffer;
            }


            /**
             * @param src the input string
             * @param regex the regex that will be matched against the src
            */
            bool contains(std::string src, std::regex regex){
                return std::regex_search(src.begin(), src.end(), regex);
            }


            bool equalsIgnoreCase(std::string s1, std::string s2){
                return toLower(s1).compare(toLower(s2)) == 0;
            }

            size_t findFirstOf(std::string src, std::regex regex){
                std::smatch match;
                std::regex_search(src, match, regex);
                return (size_t) match.position();
            }
            size_t findLastOf(std::string src, std::regex regex){
                std::string cp = src;
                std::reverse(cp.begin(), cp.end());
                return src.size() - 1 - findFirstOf(cp, regex);
            }
        }
    
    }
}

#endif