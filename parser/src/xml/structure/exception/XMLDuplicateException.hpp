/**
 * @file
 * 
 * An XMLDuplicateException is thrown whenever a duplicate attribute is found for an element
 * 
 * @author Gabriele-P03
 * @date 27-09-2024
 */
#ifndef XML_DUPLICATE_EXCEPTION_JPL
#define XML_DUPLICATE_EXCEPTION_JPL

#include "XMLException.hpp"

namespace jpl{
    namespace _parser{
        namespace _xml{
            namespace _exception{
        
                class XMLDuplicateException : public XMLException{
                    
                    public:

                        XMLDuplicateException(std::string msg) : XMLException("XMLDuplicateException", msg){
                            #ifdef AUTO_LOG_EXCEPTION_JPL
                                _logger::error(this->getStacktraceAsString());
                            #endif
                        }
                        XMLDuplicateException() : XMLDuplicateException(""){}

                };
            }
        }
    }
}

#endif