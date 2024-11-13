#include "DTDUtils.hpp"

const jpl::_parser::_dtd::Element* jpl::_parser::_dtd::PCDATA_ELEMENT = new jpl::_parser::_dtd::Element(jpl::_parser::_dtd::PCDATA, nullptr, jpl::_parser::_dtd::TYPE_LIST::MIXED, nullptr);

const std::regex jpl::_parser::_dtd::attr_value_regex = std::regex("#FIXED|#IMPLIED|#REQUIRED");

const jpl::_parser::_dtd::DTD* jpl::_parser::_dtd::parse(std::istream &is, std::string rootName){

    std::string line;
    if(rootName.empty()){
        if(!std::getline(is, line, '\n')){
            throw jpl::_parser::_dtd::_exception::DTDParsingException("Error during getline for DOCTYPE tag");
        }
        line = jpl::_utils::_string::startTrim(line);
        if(!line.find(DOCTYPE_TAG) == 0){
            throw jpl::_parser::_dtd::_exception::DTDParsingException("This DTD istream need to begin with DOCTYPE tag");
        }
        line = jpl::_utils::_string::startTrim(line.substr(strlen(DOCTYPE_TAG)));
        size_t spaceI = line.find(" ");
        if(spaceI == std::string::npos)
            spaceI = line.size();
        line = line.substr(0, spaceI);
        rootName = line;
    }
    jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Entity*>* entities = new jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Entity*>();
    jpl::_parser::_dtd::Element* root = new jpl::_parser::_dtd::Element(rootName);
    jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*>* buffer = new jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*>();
    buffer->add(root);
    while( std::getline(is, line, '>') ){
        line = jpl::_utils::_string::startTrim(line);
        size_t spaceI = line.find(" ");
        std::string tp = line.substr(0, spaceI+1);
        if(tp.compare(ELEMENT_TAG) == 0){
            jpl::_parser::_dtd::parseElement(line, *buffer);
        }else if(tp.compare(ATTLIST_TAG) == 0){
            jpl::_parser::_dtd::parseAttList(line, *buffer);
        }else if(tp.compare(ENTITY_TAG) == 0){
            jpl::_parser::_dtd::parseEntity(line, entities);
        }

    }
    return new jpl::_parser::_dtd::DTD(
        const_cast<const jpl::_parser::_dtd::Element*>(root),
        const_cast<const jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*>*>(buffer),
        const_cast<const jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Entity*>*>(entities));
}

std::string jpl::_parser::_dtd::parseName(const std::string &buffer, const char* decl_type){
    std::string tmp = buffer.substr(strlen(decl_type));
    size_t spaceI = tmp.find(" ");
    size_t ob = tmp.find("(");
    if(spaceI >= ob){
        throw jpl::_parser::_dtd::_exception::DTDParsingException("A declaration of an element/attribute/attlist must be followed by an empty space before attributes-list/children: " + buffer);
    }
    tmp = tmp.substr(0, spaceI);
    return tmp;
}

void jpl::_parser::_dtd::parseAttList(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*> &elements){
    std::string name = jpl::_parser::_dtd::parseName(buffer, jpl::_parser::_dtd::ATTLIST_TAG);  //Get element name
    buffer = jpl::_utils::_string::trim( buffer.substr(strlen(jpl::_parser::_dtd::ATTLIST_TAG) + name.size()) );
    jpl::_parser::_dtd::Element* cr = jpl::_parser::_dtd::tryGetElementByNameInList(name, elements);
    while(!buffer.empty()){
        size_t i = buffer.find("\n");
        if(i == std::string::npos){
            i = buffer.size();
        }
        std::string tmp = buffer.substr(0, i);
        buffer.erase(0, i);
        buffer = jpl::_utils::_string::trim(buffer);
        jpl::_parser::_dtd::Attribute* attribute = jpl::_parser::_dtd::parseAttribute(tmp, name);
    }
}

jpl::_parser::_dtd::Attribute* jpl::_parser::_dtd::parseAttribute(std::string &buffer, const std::string &elementName){
    size_t end = buffer.find(" ");
    if(end >= buffer.size()){
        throw jpl::_parser::_dtd::_exception::DTDParsingException("The attribute declaration does not contains any information. Element: " + elementName);
    }
    std::string name = buffer.substr(0, end);
    buffer.erase(0, end+1); //+1 to remove space
    end = buffer.find(" "); //ATTR_TYPE
    if(end >= buffer.size()){
        throw jpl::_parser::_dtd::_exception::DTDParsingException("The attribute declaration does not contains any information. Element: " + elementName);
    }
    std::string attr_type_str = buffer.substr(0, end);
    jpl::_parser::_dtd::ATTR_TYPE attr_type = jpl::_parser::_dtd::getATTR_TYPEByString(attr_type_str);
    jpl::_utils::_collections::_list::LinkedList<std::string>* values = nullptr;
    if(attr_type == jpl::_parser::_dtd::ATTR_TYPE::LIST_CHOICE){
        jpl::_parser::_dtd::parseListChoiceAttribute(attr_type_str, values, name, elementName);
    }
    buffer.erase(0, end+1);
    end = buffer.find(" ");
    if(end == std::string::npos){
        end = buffer.size();    //Since attr_value may be the last info about an attribute
    }
    std::string attr_value_str = buffer.substr(0, end);
    buffer.erase(0, end);
    std::string value;
    jpl::_parser::_dtd::ATTR_VALUE attr_value = jpl::_parser::_dtd::ATTR_VALUE::DEFAULT;
    if(jpl::_utils::_string::startWith(attr_value_str, jpl::_parser::_dtd::attr_value_regex)){
        attr_value = jpl::_parser::_dtd::getATTR_VALUEByString(attr_value_str);
        value = jpl::_utils::_string::startTrim(buffer);
    }else{
        value = attr_value_str;
    }
    return new jpl::_parser::_dtd::Attribute(
        name, attr_type, attr_value, value, values
    );
}

void jpl::_parser::_dtd::parseElement(const std::string &buffer, jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*> &elements){
    std::string name = jpl::_parser::_dtd::parseName(buffer, jpl::_parser::_dtd::ELEMENT_TAG);
    std::string tmp = jpl::_utils::_string::trim( buffer.substr(strlen(ELEMENT_TAG) + name.size()) );
    jpl::_parser::_dtd::Element* cr = jpl::_parser::_dtd::tryGetElementByNameInList(name, elements);
    const jpl::_parser::_dtd::TYPE_LIST type_list = jpl::_parser::_dtd::getTYPE_LISTByName(tmp.c_str());
    cr->setTypeList(type_list);
    if(type_list == jpl::_parser::_dtd::TYPE_LIST::CHILDREN){
        jpl::_parser::_dtd::parseElementList(tmp, elements, cr->getElementList());
        jpl::_parser::_dtd::trySetMixedElementList(cr);
    }
}

void jpl::_parser::_dtd::parseElementList(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*> &elements, jpl::_parser::_dtd::ElementList* &elementList){
    bool flagParsePRS_OP = true;
    jpl::_parser::_dtd::OCC_OP occ_op = jpl::_parser::_dtd::getOCC_OPByName(buffer.at(buffer.size()-1));
    if(occ_op != jpl::_parser::_dtd::OCC_OP::MANDATORY){
        buffer.erase(buffer.size()-1, 1);
    }
    elementList->setOCC_OP(occ_op);
    buffer = buffer.erase(0, 1);    //Remove opening bracket
    buffer = buffer.erase(buffer.size()-1, 1);  //remove closing bracket
    while(!buffer.empty()){
        jpl::_utils::_string::RegexMatch m = jpl::_utils::_string::findFirstOf(buffer, std::regex("\\(", std::regex_constants::extended));    //Looking for the sub-elementList
        jpl::_utils::_string::RegexMatch x = jpl::_utils::_string::findFirstOf(buffer, std::regex(",|\\|", std::regex_constants::extended));    //Single elememt
        if(x.pos < m.pos || (x.pos == m.pos && x.length == m.length)){
            std::string elementUnparsed = jpl::_utils::_string::trim(buffer.substr(0, x.pos));
            const OCC_OP occ_op = jpl::_parser::_dtd::getOCC_OPByName(elementUnparsed.at(elementUnparsed.size()-1));
            //Manca il parsing dei PCDATA
            std::string nameElement = elementUnparsed;
            if(occ_op != jpl::_parser::_dtd::OCC_OP::MANDATORY){
                nameElement.erase(nameElement.size()-1, 1); //Erase OCC_OP sign
            }
            jpl::_parser::_dtd::Element* element = jpl::_parser::_dtd::tryGetElementByNameInList(nameElement, elements);
            jpl::_parser::_dtd::Element_OCC* element_OCC = new jpl::_parser::_dtd::Element_OCC(element, occ_op);
            elementList->addElement_OCC(element_OCC);
            buffer.erase(0, elementUnparsed.size());
            if(!buffer.empty()){    //Let's check out the PRS_OP sign
                char sign = buffer.at(0);
                if(sign == ')'){
                    buffer.erase(0,1);  //Remove the closing bracket
                    if(buffer.empty()){
                        break;
                    }
                    sign = buffer.at(0);//If the buffer is not over, it has to check the PRS_OP
                }
                const jpl::_parser::_dtd::PRS_OP prs_op = jpl::_parser::_dtd::getPRS_OPByName(sign);
                if(flagParsePRS_OP){
                    flagParsePRS_OP = false;
                    elementList->setPRS_OP(prs_op);
                }else{
                    if(prs_op != elementList->getPRS_OP()){
                        throw jpl::_parser::_dtd::_exception::DTDParsingException("Presence operator overloading for element list");
                    }
                }
                buffer.erase(0,1);
                buffer = jpl::_utils::_string::trim(buffer);
            }
        }else{        
            if(m.pos != buffer.size()){
                jpl::_parser::_dtd::ElementList* subElementList = new jpl::_parser::_dtd::ElementList(); 
                elementList->addElementList(subElementList);
                parseElementList(buffer, elements, subElementList);
            }
        }
    }
}


jpl::_parser::_dtd::Element* jpl::_parser::_dtd::tryGetElementByNameInList(
    const std::string& name, 
    jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*> &elements) noexcept{
    if(name.compare(jpl::_parser::_dtd::PCDATA_TAG) == 0){
        return const_cast<jpl::_parser::_dtd::Element*>(jpl::_parser::_dtd::PCDATA_ELEMENT);
    }
    jpl::_parser::_dtd::Element* cr = jpl::_parser::_dtd::getElementByNameInList(name, elements);
    if(cr == nullptr){
        cr = new jpl::_parser::_dtd::Element(name);
        elements.add(cr);
    }
    return cr;
}

jpl::_parser::_dtd::Element* jpl::_parser::_dtd::getElementByNameInList(
    const std::string& name, 
    const jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element*> &elements) noexcept{
        for(size_t i = 0; i < elements.getSize(); i++){
            jpl::_parser::_dtd::Element* cr = elements.get(i);
            if(cr->getName().compare(name) == 0){
                return cr;
            }
        }
        return nullptr;
}

const jpl::_parser::_dtd::OCC_OP jpl::_parser::_dtd::getOCC_OPByName(const char sign){
    switch (sign)
    {
        case '?':
            return jpl::_parser::_dtd::OCC_OP::SINGLE;
        break;
        case '+':
            return jpl::_parser::_dtd::OCC_OP::LEAST;
        break;
        case '*':
            return jpl::_parser::_dtd::OCC_OP::ANY;
        break;
        default:
            return jpl::_parser::_dtd::OCC_OP::MANDATORY;
    }
}

const jpl::_parser::_dtd::PRS_OP jpl::_parser::_dtd::getPRS_OPByName(const char sign){
    switch (sign)
    {
        case ',':
            return jpl::_parser::_dtd::PRS_OP::SEQ;
        break;
        case '|':
            return jpl::_parser::_dtd::PRS_OP::CHS;
        break;
        default:
            throw jpl::_parser::_dtd::_exception::DTDParsingException("Invalid Presence Operator (',','|'): " + sign);
    }
}

const jpl::_parser::_dtd::TYPE_LIST jpl::_parser::_dtd::getTYPE_LISTByName(const char* sign){
    if(strcmp(sign, jpl::_parser::_dtd::ANY_TAG) == 0){
        return jpl::_parser::_dtd::TYPE_LIST::ANYTHING;
    }else if(strcmp(sign, jpl::_parser::_dtd::EMPTY_TAG) == 0){
        return jpl::_parser::_dtd::TYPE_LIST::EMPTY;
    }
    return jpl::_parser::_dtd::TYPE_LIST::CHILDREN;
}

const std::string& jpl::_parser::_dtd::getNameByElementPtr(const jpl::_parser::_dtd::Element* element){
    return element->getName();
}

void jpl::_parser::_dtd::trySetMixedElementList(jpl::_parser::_dtd::Element* element){
    if(element == nullptr){
        throw jpl::_exception::IllegalArgumentException("Element given is nullptr");
    }
    jpl::_parser::_dtd::ElementList* elementList = element->getElementList();
    if(!elementList->getElementList()->isEmpty() || elementList->getPRS_OP() != jpl::_parser::_dtd::PRS_OP::CHS){
        return;
    }
    const jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Element_OCC*>* elements = elementList->getElements();
    if(!elements->isEmpty()){
        if(elements->get(0)->element == jpl::_parser::_dtd::PCDATA_ELEMENT){
            element->setTypeList(jpl::_parser::_dtd::TYPE_LIST::MIXED);
        }
    }
    return;
}

const jpl::_parser::_dtd::ATTR_TYPE jpl::_parser::_dtd::getATTR_TYPEByString(const std::string &buffer){
    if(buffer.compare(jpl::_parser::_dtd::PCDATA_TAG) == 0){
        return jpl::_parser::_dtd::ATTR_TYPE::CDATA;
    }else if(buffer.at(0) == '(' && buffer.at(buffer.size()-1) == ')'){
        return jpl::_parser::_dtd::ATTR_TYPE::LIST_CHOICE;
    }else if(buffer.compare(jpl::_parser::_dtd::ID_TAG) == 0){
        return jpl::_parser::_dtd::ATTR_TYPE::ID;
    }
    throw jpl::_parser::_dtd::_exception::DTDParsingException("Attr Type not recognized: " + buffer);
}

const jpl::_parser::_dtd::ATTR_VALUE jpl::_parser::_dtd::getATTR_VALUEByString(const std::string &buffer){
    if(buffer.compare(jpl::_parser::_dtd::REQ_VALUE_ATTR_TAG) == 0){
        return jpl::_parser::_dtd::ATTR_VALUE::REQUIRED;
    }else if(buffer.compare(jpl::_parser::_dtd::IMP_VALUE_ATTR_TAG) == 0){
        return jpl::_parser::_dtd::ATTR_VALUE::IMPLIED;
    }else if(buffer.compare(jpl::_parser::_dtd::FIX_VALUE_ATTR_TAG) == 0){
        return jpl::_parser::_dtd::ATTR_VALUE::FIXED;
    }
    throw jpl::_parser::_dtd::_exception::DTDParsingException("Attr Type not recognized: " + buffer);
}

void jpl::_parser::_dtd::parseListChoiceAttribute(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<std::string>* &values,
    const std::string &nameAttribute, const std::string &nameElement){
    if(values == nullptr){
        values = new jpl::_utils::_collections::_list::LinkedList<std::string>();
    }
    if(buffer.at(0) != '(' || buffer.at(buffer.size()-1) != ')'){
        throw jpl::_parser::_dtd::_exception::DTDParsingException("An attribute's choices-list must be enclosed by round brackets: " + buffer);
    }
    buffer.erase(0,1);
    buffer.erase(buffer.size()-1,1);
    while(!buffer.empty()){
        size_t i = buffer.find(",");
        if(i == std::string::npos){
            i = buffer.size();
        }
        std::string value = buffer.substr(0, i);
        if(value.empty()){
            throw jpl::_parser::_dtd::_exception::DTDParsingException("It is trying to parse an empty value for a list choices. Attribute: " + nameAttribute + ". Element: " + nameElement);
        }
        buffer.erase(0, i+1);   //Even if it tries to remove more chars than buffer contains, it does not throw any exception
        for(size_t j = 0; j < values->getSize(); j++){
            std::string cr = values->get(j);
            if(cr.compare(value) == 0){
                throw jpl::_parser::_dtd::_exception::DTDDuplicateException("The attribute " + nameAttribute + " of " + nameElement + " already contains " + value + " value");
            }
        }
        values->add(value);
    }
}

void jpl::_parser::_dtd::parseEntity(std::string &buffer, jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_dtd::Entity*>* &entities){
    std::string name = jpl::_parser::_dtd::parseName(buffer, jpl::_parser::_dtd::ENTITY_TAG);
    buffer.erase(0, strlen(ENTITY_TAG) + name.size());
    buffer = jpl::_utils::_string::startTrim(buffer);
    jpl::_parser::_dtd::ENTITY_TYPE entity_type = jpl::_parser::_dtd::ENTITY_TYPE::INTERNAL;
    if(jpl::_utils::_string::startWith(buffer, std::regex(jpl::_parser::_dtd::SYSTEM_TAG))){
        entity_type = jpl::_parser::_dtd::ENTITY_TYPE::SYSTEM;
        buffer.erase(0, strlen(jpl::_parser::_dtd::SYSTEM_TAG));
        buffer = jpl::_utils::_string::trim(buffer);
    }
    if(buffer.empty()){
        throw jpl::_parser::_dtd::_exception::DTDParsingException("It seems like that " + name + " entity does not have a value/uri/url");
    }
    if(entity_type == jpl::_parser::_dtd::ENTITY_TYPE::SYSTEM){   //Let's check if an external entity has a well-formed value: enclosed by either single or double quotes
        if(buffer.size() < 3){
            throw jpl::_parser::_dtd::_exception::DTDParsingException("The " + name + " entity's URL/URI of a DTD entity, since it has to be enclosed by either single or double quotes, must be at least 3 chars long");
        }
        char s = buffer.at(0), e = buffer.at(buffer.size()-1);
        if( (s == '\'' && e == '\'') || (s == '\"' && e == '\"') ){
            buffer = buffer.substr(1, buffer.size()-2);
        }else{
            throw jpl::_parser::_dtd::_exception::DTDParsingException("The " + name + " entity's URL/URI must be enclosed by either single or double quotes: " + buffer);
        }
    }
    jpl::_parser::_dtd::Entity* entity = new jpl::_parser::_dtd::Entity(entity_type, name, buffer);
    entities->add(entity);
}