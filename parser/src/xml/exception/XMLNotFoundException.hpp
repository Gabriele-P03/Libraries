/**
 * @file
 * 
 * An XMLNotFoundException is thrown whenever an either Element or Attribute name-based getter is invoked and no fields 
 * had been found
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef XML_NOT_FOUND_EXCEPTION_JPL
#define XML_NOT_FOUND_EXCEPTION_JPL

#include "XMLException.hpp"

namespace jpl{
    namespace _parser{
        namespace _xml{
            namespace _exception{
        
                class XMLNotFoundException : public XMLException{
                    
                    public:

                        XMLNotFoundException(std::string msg) : XMLException("XMLNotFoundException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        XMLNotFoundException() : XMLNotFoundException(""){}

                };
            }
        }
    }
}

#endif