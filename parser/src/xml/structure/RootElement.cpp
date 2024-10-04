#include "RootElement.hpp"

jpl::_parser::_xml::RootElement::RootElement(std::string name) : 
    jpl::_parser::_xml::RootElement::RootElement(name, "1.0", "UTF-8"){

}

jpl::_parser::_xml::RootElement::RootElement(std::string name, std::string version, std::string encoding) : 
    jpl::_parser::_xml::RootElement::RootElement(name, version, encoding, 
        "",
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Element*>(),
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Attribute*>()){

}

jpl::_parser::_xml::RootElement::RootElement(std::string name, std::string version, std::string encoding,
        std::string text,
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Element*> elements,
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Attribute*> attributes) : 
        jpl::_parser::_xml::Element::Element(name, text, 0, elements, attributes){
            this->version = version;
            this->encoding = encoding;
}

std::string jpl::_parser::_xml::RootElement::toString() const noexcept{
    std::string buffer = "<?xml version=\"" + this->version + "\" encoding=\"" + this->encoding + "\" ?>";
    buffer += "\n" + jpl::_parser::_xml::Element::toString();
    return buffer;
}