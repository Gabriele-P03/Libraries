/**
 * 
 * @file
 * 
 * The rappresentation of an XML root element
 * Version is set by RootElement(std::string) as "1.0"
 * Encoding is set by RootElement(std::string) as "UTF-8"
 * Tabs is set as 0 by default for Root Element 
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */

#ifndef XML_ROOT_ELEMENT_JPL
#define XML_ROOT_ELEMENT_JPL

#include "Element.hpp"

namespace jpl{
    
    namespace _parser{
        
        namespace _xml{

            class RootElement : public Element{

                protected:

                    /**
                     * The version used by this root element
                     */
                    std::string version;
                    /**
                     * The encoding used by this root element
                     */
                    std::string encoding;
                
                public:

                    /**
                     * Instance a new XML Root element
                     * 
                     * @param name 
                     * 
                     * @throw XMLValidationException if name does not respect XML Syntax 
                     */            
                    RootElement(std::string name);
                    /**
                     * Instance a new XML Root element
                     * 
                     * @param name 
                     * @param version
                     * @param encoding
                     * @param text
                     * @param elements list of children elements
                     * @param attributes list of attributes
                     * 
                     * @throw XMLValidationException if name does not respect XML Syntax 
                     */
                    RootElement(std::string name, std::string version, std::string encoding);
                    RootElement(std::string name, std::string version, std::string encoding,
                        std::string text, 
                        _utils::_collections::_list::LinkedList<Element*> elements,
                        _utils::_collections::_list::LinkedList<Attribute*> attributes);

                    std::string getVersion() const noexcept {return this->version;}
                    std::string getEncoding() const noexcept {return this->encoding;}

                    /**
                     * @return the representation of the current root element as XML Syntax requires
                     */
                    std::string toString() const noexcept override;

            };

        }
    }
}



#endif