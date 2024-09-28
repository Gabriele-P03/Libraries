/**
 * @file
 * 
 * An XMLParsingException is thrown whenever an either attribute or element of an XML file is ill-formed
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef XML_PARSING_EXCEPTION_JPL
#define XML_PARSING_EXCEPTION_JPL

#include "XMLException.hpp"

namespace jpl{
    namespace _parser{
        namespace _xml{
            namespace _exception{
        
                class XMLParsingException : public XMLException{
                    
                    public:

                        XMLParsingException(std::string msg) : XMLException("XMLParsingException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        XMLParsingException() : XMLParsingException(""){}

                };
            }
        }
    }
}

#endif