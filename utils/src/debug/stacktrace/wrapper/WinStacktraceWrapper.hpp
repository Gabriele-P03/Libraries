/**
 * @file
 * 
 * This is the right Stacktrace Wrapper for a windows machine.
 * You oughta never include this header directly: kernel check is performed by StacktraceWrapper - whose header file may give you
 * more information with its documentation 
 * 
 * @author Gabriele-P03
 * @date 2023-08-03
 * @copyright Copyright (c) 2023
 */

#ifndef WIN_STACKTRACE_WRAPPER_JPL
#define WIN_STACKTRACE_WRAPPER_JPL

    #include <eh.h>
    #include <Windows.h>
    #include <dbghelp.h>
    #include <string>
    #include <vector>   //It will be replaced by JPL's ArrayList
    #include "../../ErrorUtils.hpp"

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

                    std::vector<Frame>* frames = new std::vector<Frame>();

                    HANDLE process = GetCurrentProcess();
                    HANDLE thread = GetCurrentThread();

                    //Capturing context
                    CONTEXT context;
                    memset(&context, 0, sizeof(context));
                    context.ContextFlags = CONTEXT_FULL;
                    RtlCaptureContext(&context);

                    //Initializing process
                    if (SymInitialize(process, NULL, TRUE)) {

                        DWORD image;
                        STACKFRAME64 stackframe;
                        ZeroMemory(&stackframe, sizeof(STACKFRAME64));

                        #ifdef _M_IX86
                            image = IMAGE_FILE_MACHINE_I386;
                            stackframe.AddrPC.Offset = context.Eip;
                            stackframe.AddrPC.Mode = AddrModeFlat;
                            stackframe.AddrFrame.Offset = context.Ebp;
                            stackframe.AddrFrame.Mode = AddrModeFlat;
                            stackframe.AddrStack.Offset = context.Esp;
                            stackframe.AddrStack.Mode = AddrModeFlat;
                        #elif _M_X64
                            image = IMAGE_FILE_MACHINE_AMD64;
                            stackframe.AddrPC.Offset = context.Rip;
                            stackframe.AddrPC.Mode = AddrModeFlat;
                            stackframe.AddrFrame.Offset = context.Rsp;
                            stackframe.AddrFrame.Mode = AddrModeFlat;
                            stackframe.AddrStack.Offset = context.Rsp;
                            stackframe.AddrStack.Mode = AddrModeFlat;
                        #elif _M_IA64
                            image = IMAGE_FILE_MACHINE_IA64;
                            stackframe.AddrPC.Offset = context.StIIP;
                            stackframe.AddrPC.Mode = AddrModeFlat;
                            stackframe.AddrFrame.Offset = context.IntSp;
                            stackframe.AddrFrame.Mode = AddrModeFlat;
                            stackframe.AddrBStore.Offset = context.RsBSP;
                            stackframe.AddrBStore.Mode = AddrModeFlat;
                            stackframe.AddrStack.Offset = context.IntSp;
                            stackframe.AddrStack.Mode = AddrModeFlat;
                        #endif

                        //Let's StackWalk
                        for(unsigned int i = 0; i < maxSize; i++){

                            bool flag = StackWalk64(
                                image, process, thread, 
                                &stackframe, &context, NULL, 
                                SymFunctionTableAccess64, SymGetModuleBase64, NULL
                            ); 

                            /*
                                Actually, any error occurred: there are no frames to walk thorugh left
                            */
                            if(!flag){
                                break;
                            }

                            DWORD64  dwDisplacement = 0;
                            DWORD64  dwAddress = stackframe.AddrPC.Offset;

                            char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
                            PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
                            pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
                            pSymbol->MaxNameLen = MAX_SYM_NAME;

                            //Let's get Symbol from address
                            if( SymFromAddr( process, stackframe.AddrPC.Offset, &dwDisplacement, pSymbol ) ){
                                            
                                //Let's get number line
                                DWORD disLine = 0;
                                IMAGEHLP_LINE64 line;
                                ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
                                line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

                                if ( SymGetLineFromAddr64(process, dwAddress, &disLine, &line) ){                                                        
                                    //Everything ok. Let's add the frame to the vector
                                    Frame frame(line.LineNumber-1, std::string(pSymbol->Name), std::to_string(pSymbol->Address), std::string(line.FileName));
                                    frames->push_back(frame);
                                    continue;
                                }
                            }

                            frames->push_back(Frame());
                        }
                        SymCleanup(process);

                        //Let's remove skipped frames
                        if(frames->size()-skipped > 0)
                            frames->erase(frames->begin(), frames->begin()+skipped);

                    }
                    return frames;
                }
            }
        }
    }

#endif