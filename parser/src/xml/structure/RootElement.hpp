/**
 * 
 * @file
 * 
 * THe rappresentation of an XML root element
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */

#ifndef XML_ROOT_ELEMENT_JPL
#define XML_ROOT_ELEMENT_JPL

#include <Element.hpp>

namespace jpl{
    
    namespace _parser{
        
        namespace _xml{

            class Root : public Element{

                protected:

                    std::string version;
                    std::string encoding;
                
                public:


                    Root(std::string name);
                    Root(std::string name, std::string version, std::string encoding);
                    Root(std::string name, std::string version, std::string encoding, 
                        _utils::_collections::_list::LinkedList<Element> elements,
                        _utils::_collections::_list::LinkedList<Attribute> attributes);

                    std::string getVersion() const noexcept {return this->version;}
                    std::string getEncoding() const noexcept {return this->encoding;}

            };

        }
    }
}



#endif