/**
 * XML Parser Utils
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
            
            /**
             * It parse header of XML Root Element which contains version and encoding information
             * @param buffer 
             * @param nameAttribute
             * @param attributeOut it will contains the value of nameAttribute
             */
            static void parseHeaderAttribute(std::string &buffer, std::string nameAttribute, std::string &attributeOut);

            static void parseHeaders(const RootElement* root);

            static void parseElement(std::string &buffer, Element* element, unsigned short tabs);
            static void parseAttributes(std::string buffer, Element* element);

            /**
             * It validates name as XML Syntax requires: only letters, digits, hyphens, underscores and period are allowed
             * @param name
             * @throw XMLValidationException if name does not respect XML Syntax
             */
            extern void validateName(const std::string &name);

            RootElement* parse(std::istream &is);
        }
    }
}

#endif