/**
 * @file
 * 
 * This is the right Stacktrace Wrapper for a linux machine.
 * You oughta never include this header directly: kernel check is performed by StacktraceWrapper - whose header file may give you
 * more information with its documentation 
 * 
 * @author Gabriele-P03
 * @date 2023-08-03
 * @copyright Copyright (c) 2023
 */

#ifndef LINUX_STACKTRACE_WRAPPER_JPL
#define LINUX_STACKTRACE_WRAPPER_JPL

    #include <string>
    #include <vector>   //It will be replaced by JPL's ArrayList
    #include "../../ErrorUtils.hpp"
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
                            std::string sbuffer = std::string(c_c_buffer[i]);

                            unsigned long p = sbuffer.find('(');

                            //Store into syscom the formatted string
                            char syscom[512];
                            sprintf(syscom, "addr2line %p -fCe %.*s", buffer[i], p, c_c_buffer[i]);

                            FILE* pipe = popen(syscom, "r");
                            if(!pipe){
                                frames->push_back(Frame());
                            }else{

                                //Used as buffer
                                std::string tmpString = "";
                                // read till end of process:
                                while (!feof(pipe)) {
                                    
                                    char tmp[128];
                                    // use buffer to read and add to result
                                    if (fgets(&tmp[0], 128, pipe) != NULL)
                                        tmpString += std::string(tmp);
                                }

                                if(!tmpString.empty()){
                                    //File name before ':', after that is the line number
                                    unsigned long endOfFuncName = tmpString.find('\n'); 
                                    unsigned long splitIndex = tmpString.find(':', endOfFuncName);

                                    unsigned long endOfLine = tmpString.find(' ', splitIndex);
                                    //Since ' ' has to be checked only if discriminator is found ot, otherwise \n 
                                    if(endOfLine == std::string::npos){
                                        endOfLine = tmpString.find('\n', splitIndex);
                                    }

                                    if(splitIndex != std::string::npos && endOfFuncName != std::string::npos && endOfLine != std::string::npos){
                                        std::string file_name = tmpString.substr(endOfFuncName+1, splitIndex-endOfFuncName-1);
                                        std::string func_name = tmpString.substr(0, endOfFuncName);

                                        char p_addr[32];
                                        sprintf(p_addr, "%p", buffer[i]);
                                        std::string address = std::string(p_addr);

                                        Da mettere dentro un try-catch
                                        unsigned long lineNumber = std::stoi(tmpString.substr(splitIndex+1, endOfLine-splitIndex-1));

                                        frames->push_back(Frame(lineNumber, func_name, address, file_name));
                                    }else{
                                        frames->push_back(Frame());
                                    }
                                }else{
                                    frames->push_back(Frame());
                                }
                                
                                pclose(pipe);
                            }
                        }
                        free(c_c_buffer);
                    }

                    return frames;
                }
            }
        }
    }


#endif
