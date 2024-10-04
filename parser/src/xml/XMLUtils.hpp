/**
 * XML Parser
 * 
 * @author Gabriele-P03
 * @date 1-10-2024
 */

#ifndef XML_PARSER_JPL
#define XML_PARSER_JPL

#include "structure/RootElement.hpp"
#include "exception/XMLValidationException.hpp"
#include <jpl/utils/StringUtils.hpp>

namespace jpl{
    namespace _parser{
        namespace _xml{
            
            static void parseHeaderAttribute(std::string &buffer, std::string nameAttribute, std::string &attributeOut);

            static void parseElement(std::string &buffer, Element* element, unsigned short tabs);
            static void parseAttributes(std::string buffer, Element* element);
            void validateName(std::string name);

            RootElement* parse(std::string buffer);
        }
    }
}

#endif