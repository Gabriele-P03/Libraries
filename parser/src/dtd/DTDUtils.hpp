/**
 * @file
 * 
 * This header file contains some DTD utility functions
 * 
 * @author Gabriele-P03
 */

#ifndef DTD_UTILS_JPL
#define DTD_UTILS_JPL

#include "DTD.hpp"
#include <jpl/utils/StringUtils.hpp>
#include "exception/DTDParsingException.hpp"

namespace jpl{
    namespace _parser{

        namespace _dtd{
            extern const std::regex attr_value_regex;

            extern const Element* PCDATA_ELEMENT;

            const DTD* parse(std::istream &is, std::string rootName = "");

            /**
             * @param buffer - single line to parse
             * @param decl_type ELEMENT_TAG, ATTLIST_TAG or ENTITY_TAG
             * @return the name of the given element/attribute as std::string
             */
            static std::string parseName(const std::string &buffer, const char* decl_type);

            static void parseAttList(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<Element*> &elements);
            
            static Attribute* parseAttribute(std::string &buffer, const std::string &elementName);

            static void parseElement(const std::string &buffer, jpl::_utils::_collections::_list::LinkedList<Element*> &elements);

            static void parseElementList(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<Element*> &elements, ElementList* &elementList);

            static Element* tryGetElementByNameInList(const std::string& name, jpl::_utils::_collections::_list::LinkedList<Element*> &elements) noexcept;

            static Element* getElementByNameInList(const std::string& name, const jpl::_utils::_collections::_list::LinkedList<Element*> &elements) noexcept;

            static const OCC_OP getOCC_OPByName(const char sign);
            static const PRS_OP getPRS_OPByName(const char sign);

            static const ATTR_TYPE getATTR_TYPEByString(const std::string &buffer);
            static const ATTR_VALUE getATTR_VALUEByString(const std::string &buffer);

            static void parseListChoiceAttribute(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<std::string>* &values, const std::string &nameAttribute, const std::string &nameElement);

            static const TYPE_LIST getTYPE_LISTByName(const char* sign);

            static void trySetMixedElementList(Element* element);

            const std::string& getNameByElementPtr(const Element* element);

            void parseEntity(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<Entity*>* &entities);
        }
    }
}


#endif