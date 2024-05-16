/**
 * 
*/

#ifndef FRAME_STACKTRACE_JPL
#define FRAME_STACKTRACE_JPL

#include <string>

namespace jpl{
    namespace _utils{
        namespace _debug{

            struct Frame{
                const bool frame_valid;
                const unsigned long line;
                const std::string function_name;
                const std::string address;
                const std::string file_name;

                Frame(const unsigned long line, const std::string function_name, const std::string address, const std::string file_name) : 
                    frame_valid(true), line(line), function_name(function_name), address(address), file_name(file_name){}
                
                Frame() : frame_valid(false), line(0), function_name(""), address(""), file_name(""){}
                
                Frame& operator=(const Frame& frame){
                    *const_cast<bool*>(&this->frame_valid) = frame.frame_valid;
                    *const_cast<unsigned long*>(&this->line) = frame.line;
                    *const_cast<std::string*>(&this->function_name) = frame.function_name;
                    *const_cast<std::string*>(&this->address) = frame.address;
                    *const_cast<std::string*>(&this->file_name) = frame.file_name;
                    return *this;
                }
            };
        }
    }
}

#endif