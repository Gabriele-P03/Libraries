/**
 * 
 * SPLIT FUNCTION
 * 
*/

#ifndef STRING_UTILS_JPL
#define STRING_UTILS_JPL

    #ifdef AUTO_LOG_EXCEPTION_JPL
        #include <jpl/logger/LoggerWrapper.hpp>
    #endif
    
#include <string>
#include "structure/list/LinkedList.hpp"
#include <regex>
#include <algorithm>

namespace jpl{
    namespace _utils{
        namespace _string{

            struct RegexMatch{
                /**
                 * It is the position where match begins
                */
                size_t pos;
                /**
                 * It is the length of the match (contained chars)
                */
                size_t length;
                RegexMatch(size_t pos, size_t length){
                    this->pos = pos;
                    this->length = length;
                }
            }; 

            /**
             * @return Splitted src using regex
             * @param src
             * @param regex
            */
            _collections::_list::LinkedList<std::string>* split(const std::string &src, const std::regex &regex);


            /**
             * @brief Trim the beginning of given std::string
             * @param src
             * @return src 
            */
            inline std::string startTrim(const std::string &src){
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
            inline std::string endTrim(const std::string &src){
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
            inline std::string trim(const std::string &src){
                return jpl::_utils::_string::startTrim(jpl::_utils::_string::endTrim(src));
            }


            /**
             * @param src the input string
             * @param regex the std::basic_regex which will be matched against src
             * @param fmt the string which will be inserted 
             * @param flags the match flags, default is std::regex_constants::format_first_only   
             * @return src modified based on regex and fmt 
            */
            inline std::string replace(const std::string &src, const std::regex& regex, const std::string &fmt, const std::regex_constants::match_flag_type &flags = std::regex_constants::format_first_only){
                return std::regex_replace(src, regex, fmt, flags);
            }
            /**
             * @param src the input string
             * @param regex the std::basic_regex which will be matched against src
             * @param fmt the string which will be inserted   
             * @param flags the match flags
             * @return src modified based on regex, fmt and flags 
            */
            inline std::string replaceAll(const std::string &src, const std::regex &regex, const std::string &fmt){
                return std::regex_replace(src, regex, fmt, std::regex_constants::match_any);
            }


            /**
             * @param src the input string
             * @param regex the regex which will be matched against src
             * @return how many times the regex has been matched against src
            */
            inline size_t count(const std::string &src, const std::regex &regex){
                auto beg = std::sregex_iterator(src.begin(), src.end(), regex);
                auto end = std::sregex_iterator();
                return std::distance(beg, end);
            }


            /**
             * @param src the input string
             * @return the given input string formatted as UPPER case
            */
            inline std::string toUpper(const std::string &src){
                std::string buffer;
                std::transform(src.begin(), src.end(), buffer.begin(), ::toupper);
                return buffer;
            }
            /**
             * @param src the input string
             * @return the given input string formatted as LOWER case
            */
            inline std::string toLower(const std::string &src){
                std::string buffer;
                std::transform(src.begin(), src.end(), buffer.begin(), ::tolower);
                return buffer;
            }


            /**
             * @param src the input string
             * @param regex the regex that will be matched against the src
            */
            inline bool contains(const std::string &src, const std::regex& regex){
                return std::regex_search(src.begin(), src.end(), regex);
            }

            /**
             * @param src the input string
             * @param regex the regex that will be matched against
            */
           inline bool match(const std::string &src, const std::regex &regex){
            return std::regex_match(src.begin(), src.end(), regex);
           }


            inline bool equalsIgnoreCase(const std::string &s1, const std::string &s2){
                return toLower(s1).compare(toLower(s2)) == 0;
            }

            inline RegexMatch findFirstOf(const std::string& src, const std::regex &regex){
                std::smatch match;
                std::regex_search(src, match, regex);
                RegexMatch m = RegexMatch(match.position(), match.length());
                return m;
            }
            inline RegexMatch findLastOf(const std::string& src, const std::regex &regex){
                std::string cp = src;
                std::reverse(cp.begin(), cp.end());
                RegexMatch m = findFirstOf(cp, regex);
                m.pos = src.size() - 1 - m.pos;
                return m;
            }
            inline bool startWith(const std::string& src, const std::regex &regex){
                RegexMatch m = findFirstOf(src, regex);
                return m.pos == 0 && m.length > 0;
            }
            inline bool endWith(const std::string& src, const std::regex &regex){
                RegexMatch m = findLastOf(src, regex);
                return (m.pos + m.length == src.length());
            }

            /**
             * @brief A group is intended to be a substring which begins with o and over with c.
             * A group can have sub-group. It is used mostly through parsers.
             *   
             * 
             * @param src input string
             * @param o the regex which open the group
             * @param c the regex which close the group
             * @return index where the root-group's c begins at 
            */
            size_t getIndexGroupOver(std::string src, const std::regex &o, const std::regex &c);
        }
    
    }
}

#endif