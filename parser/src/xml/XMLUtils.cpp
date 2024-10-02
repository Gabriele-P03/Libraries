#include "XMLUtils.hpp"

jpl::_parser::_xml::RootElement* jpl::_parser::_xml::parse(std::string buffer){
    //Parsing header
    size_t end = jpl::_utils::_string::getIndexGroupOver(buffer, std::regex("<"), std::regex(">"));
    std::string header = buffer.substr(0, end+1);
    if(header.find("<?xml ") != 0){
        throw new jpl::_parser::_xml::_exception::XMLParsingException("XML Header must begin with '<?xml '");
    }
    if(header.find_last_of("?>") != header.size()-1){//-1 due to ?
        throw new jpl::_parser::_xml::_exception::XMLParsingException("XML Header must end with '?>'");
    }
    buffer = jpl::_utils::_string::trim(buffer.substr(header.size()));  //Clean buffer from header
    header = header.substr(5, header.size() - 5 - 2);   //Remove '<?xml' and '?>'
    header = jpl::_utils::_string::trim(header);
    std::string version = "1.0", encoding = "UTF-8";
    parseHeaderAttribute(header, "version", version);
    try{    //Check if version is valid
        std::atof(version.c_str());
    }catch(std::exception* ex){
        throw new jpl::_parser::_xml::_exception::XMLParsingException("Version " + version + " is not valid");
    }
    parseHeaderAttribute(header, "encoding", encoding);

    size_t endRoot = jpl::_utils::_string::getIndexGroupOver(buffer, std::regex("<"), std::regex(">"));
    if(endRoot == std::string::npos)
        throw new jpl::_parser::_xml::_exception::XMLParsingException("XML Root declaration is not valid");
    std::string tmp = jpl::_utils::_string::trim(buffer.substr(1, endRoot));
    size_t endNameRoot = tmp.find(" ");
    if(endNameRoot == std::string::npos){
        endNameRoot = tmp.find("\0");   //If there are no empty space, it may be that there are no attributes
        if(endNameRoot == std::string::npos)
            throw new jpl::_parser::_xml::_exception::XMLParsingException("XML Root declaration is not valid: " + tmp);
    }
    std::string rootName = tmp.substr(0, endNameRoot);
    validateName(rootName);
    tmp = tmp.substr(endNameRoot, tmp.size() - 1 - endNameRoot);
    buffer = buffer.substr(endRoot+1);//remove header of root
    buffer = buffer.substr(0, buffer.size() - 3 - rootName.size());//Remove angle brackets, slash and root name from the end
    RootElement* root = new RootElement(rootName, version, encoding);
    jpl::_parser::_xml::parseAttributes(tmp, root);
    return root;
}

static void jpl::_parser::_xml::parseHeaderAttribute(std::string &buffer, std::string nameAttribute, std::string &attributeOut){
    if(jpl::_utils::_string::startWith(buffer, std::regex(nameAttribute + "="))){    //Version is not mandatory
        if(buffer.at(nameAttribute.size()+1) != '\"'){
            throw new jpl::_parser::_xml::_exception::XMLParsingException("Attribute must be enclosed by double-quote");
        }
        buffer = buffer.substr(nameAttribute.size()+2);
        size_t endAttribute = buffer.find('\"');
        if(endAttribute == std::string::npos)   //Closed quote missing
            throw new jpl::_parser::_xml::_exception::XMLParsingException("Attribute must be enclosed by double-quote");
        attributeOut = buffer.substr(0, endAttribute);
        buffer = buffer.substr(endAttribute+1);
        buffer = jpl::_utils::_string::trim(buffer);
    }
}

void jpl::_parser::_xml::parseAttributes(std::string buffer, Element* element){
    buffer = jpl::_utils::_string::trim(buffer);
    while(!buffer.empty()){
        size_t eq = buffer.find('=');
        if(eq == std::string::npos)
            throw new jpl::_parser::_xml::_exception::XMLParsingException("It seems like an equal sign is missing: " + buffer);
        std::string nameAttribute = buffer.substr(0, eq);
        validateName(nameAttribute);
        buffer = buffer.substr(eq+1);
        char delimiter = buffer.at(0);
        if(delimiter == '\'' || delimiter == '\"'){
            size_t end = buffer.find(delimiter, 1);
            if(end == std::string::npos)
                throw new jpl::_parser::_xml::_exception::XMLParsingException("Attribute " + nameAttribute + " is not closed by " + delimiter);
            std::string value = buffer.substr(1, end-1);
            jpl::_parser::_xml::Attribute* attribute = new jpl::_parser::_xml::Attribute(nameAttribute, value);
            element->addAttribute(attribute);
            buffer = buffer.substr(end+1);
            buffer = jpl::_utils::_string::startTrim(buffer);
        }else{
            throw new jpl::_parser::_xml::_exception::XMLParsingException("Attribute value must be enclosed by double-quote");
        }
    }
}

void jpl::_parser::_xml::validateName(std::string name){
    if(!jpl::_utils::_string::match(name, std::regex("^[A-Za-z0-9_.-]+$", std::regex::extended))){
        throw new jpl::_parser::_xml::_exception::XMLValidationException("Name must contains only letters, digits, hyphens, underscores and periods: " + name);
    }
}