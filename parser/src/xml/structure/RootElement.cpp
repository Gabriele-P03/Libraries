#include "RootElement.hpp"

jpl::_parser::_xml::Root::Root(std::string name) : 
    jpl::_parser::_xml::Root::Root(name, "1.0", "UTF-8"){

}

jpl::_parser::_xml::Root::Root(std::string name, std::string version, std::string encoding) : 
    jpl::_parser::_xml::Root::Root(name, version, encoding, 
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Element*>(),
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Attribute*>()){

}

jpl::_parser::_xml::Root::Root(std::string name, std::string version, std::string encoding,
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Element*> elements,
        jpl::_utils::_collections::_list::LinkedList<jpl::_parser::_xml::Attribute*> attributes) : 
        jpl::_parser::_xml::Element::Element(name, elements, attributes){
            this->version = version;
            this->encoding = encoding;
}

std::string jpl::_parser::_xml::Root::toString() const noexcept{
    std::string buffer = "<?xml version=\"" + this->version + "\" encoding=\"" + this->encoding + "\"?>";
    buffer = "\n" + jpl::_parser::_xml::Element::toString();
    return buffer;
}