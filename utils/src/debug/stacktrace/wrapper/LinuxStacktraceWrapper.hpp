/**
 * @file
 * 
 * This is the right Stacktrace Wrapper for a linux machine.
 * You oughta never include this header directly: kernel check is performed by StacktraceWrapper - whose header file may give you
 * more information with its documentation 
 * 
 * (1)
 * I have already left a note about the decreasing of line number due to PC processing, as you can read from the
 * StacktraceWrapper.hpp documentation.
 * Although that, as you can see here, that decreasing operation is performed only when addr2line does NOT get into
 * a multiple path function (check the link below to get more information about it)
 * @link https://wiki.dwarfstd.org/Path_Discriminators.md
 * 
 * Please, note instead that line number is always decreased under a windows machine
 * 
 * @author Gabriele-P03
 * @date 2023-08-03
 * @copyright Copyright (c) 2023
 */

#ifndef LINUX_STACKTRACE_WRAPPER_JPL
#define LINUX_STACKTRACE_WRAPPER_JPL

    #include <string>
    #include <vector>   //It will be replaced by JPL's ArrayList
    #include <regex>
    #include <iostream>
    #include <execinfo.h>

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

                /**
                 * 
                 * @param skipped amount of frames to skip
                 * @param maxSize max amount of frames to retrieve
                 * @return std::vector<Frame>* vector containing all retrieved frames
                 */

                std::vector<Frame>* queryStacktrace(unsigned int skipped, unsigned int maxSize){

                    std::vector<Frame> *frames = new std::vector<Frame>();
                    void* buffer[maxSize];

                    //Retrieve the stacktrace 
                    int size = backtrace(buffer, maxSize);

                    //Translate symbols
                    char** c_c_buffer = backtrace_symbols(buffer, size);

                    //If it could not translate them, the vector is filled with size invalid frame
                    if(c_c_buffer == NULL){
                        frames->insert(frames->begin(), size, Frame());
                    }else{

                        for(unsigned int i = 0; i < size; i++){
                            //Convert the symbol into a string
                            std::string sbuffer = std::string(c_c_buffer[i]);
                            //Let's get file name where symbol has been found
                            std::string exeFileName;
                            unsigned long space = sbuffer.find('(');
                            if(space == std::string::npos){
                                space = sbuffer.size();
                            }
                            exeFileName = sbuffer.substr(0, space);
                            //Let's get address
                            std::string address = "";
                            unsigned long _s = sbuffer.find("(");
                            if( _s != std::string::npos && (sbuffer.find("+0x") != std::string::npos)){
                                address = sbuffer.substr(_s+1);  //Plus 1 will remove '('
                                unsigned long s_ = address.find(')');
                                if(s_ != std::string::npos){
                                    address = address.substr(0, s_);
                                }
                            }else{
                                char tmpAddr[32];
                                sprintf(&tmpAddr[0], "%p", buffer[i]);
                                address = std::string(tmpAddr);
                            }

                            char syscom[512];
                            sprintf(syscom, "addr2line -e %.*s -fC %.*s", exeFileName.size(), exeFileName.c_str(), address.size(), address.c_str());
                            FILE* cmdStream = popen(syscom, "r");

                            std::string bufferStream = "";
                            while(!feof(cmdStream)){
                                
                                char tmpStream[512];
                                if(fgets(tmpStream, 512, cmdStream) != NULL){
                                    bufferStream += tmpStream;
                                }
                            }

                            //Carriage which separate func name by file name and line
                            unsigned long cr = bufferStream.find("\n");
                            std::string func_name = bufferStream.substr(0, cr);
                            //':' separate file name and line
                            unsigned long separator = bufferStream.find(":", cr);
                            std::string file_name = bufferStream.substr(cr+1, separator-cr-1);
                            //Discriminator for multiple path function
                            unsigned long disc_index = bufferStream.find(" (discriminator");

                            unsigned long line = 0;
                            try{
                                if(disc_index != std::string::npos)
                                    line = std::stoi(bufferStream.substr(separator+1, disc_index));
                                else
                                    line = std::stoi(bufferStream.substr(separator+1)) - 1; //-1 due to PC increasing (1)
                            }catch(std::invalid_argument &ex){
                                line -= 1;  //Since it ulong, a line which could not be figured out ('?') will be stored as max value for a ulong
                            }

                            if(disc_index != std::string::npos){
                                func_name += " " + bufferStream.substr(disc_index, bufferStream.size()-disc_index-1);
                            }

                            frames->push_back(Frame(line, func_name, address, file_name));
                        }
                    }

                    return frames;
                }
            }
        }
    }


#endif
