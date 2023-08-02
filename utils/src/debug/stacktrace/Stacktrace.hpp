#ifndef STACKTRACE_JPL
#define STACKTRACE_JPL

    #include <string>
    #include <vector>

    #include "../../ErrorUtils.hpp"
#include <eh.h>
    #include <iostream>

    #ifdef __linux__

    #elif _WIN32
    
        #include <eh.h>
        #include <Windows.h>
        #include <dbghelp.h>
    #endif

    namespace jpl{

        namespace _utils{

            namespace _debug{



                class Stacktrace{

                    public:

                        struct Frame{
                            unsigned long line;
                            std::string function_name;
                            std::string address;
                            std::string file_name;
                        };

                    
                    protected:

                        Frame* frames;    //Later it will become an ArrayList

                        unsigned long size;
                        unsigned long skipped;
                        unsigned long maxSize;  //It will not be able to be retrieved since it is used only to get stacktrace

                        #ifdef _linux__

                        #elif _WIN32
                            void queryStacktrace(){

                                HANDLE process = GetCurrentProcess();
                                HANDLE thread = GetCurrentThread();

                                CONTEXT context;
                                memset(&context, 0, sizeof(context));
                                context.ContextFlags = CONTEXT_FULL;
                                RtlCaptureContext(&context);

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

                                    //Let's Stackwalk
                                    for(unsigned int i = 0; i < this->maxSize; i++){

                                        bool flag = StackWalk64(
                                            image, process, thread, 
                                            &stackframe, &context, NULL, 
                                            SymFunctionTableAccess64, SymGetModuleBase64, NULL
                                        ); 

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
                                                
                                                

                                            }else{
                                                unsigned long error = _error::_GetLastError();
                                                std::cout<<error<<" - "<<_error::_GetLastErrorAsString(error)<<std::endl;    
                                            }

                                        }else{
                                            unsigned long error = _error::_GetLastError();
                                            std::cout<<error<<" - "<<_error::_GetLastErrorAsString(error)<<std::endl;
                                        }
                                        this->size++;
                                    }

                                    SymCleanup(process);

                                    return;
                                }

                                unsigned long error = _error::_GetLastError();
                                std::cout<<error<<" - "<<_error::_GetLastErrorAsString(error)<<std::endl;
                            }
                        #endif

                    public:

                        Stacktrace(unsigned long skip, unsigned long maxSize){
                            this->skipped = skipped;
                            this->size = 0;
                            this->maxSize = maxSize;

                            this->queryStacktrace();
                        }

                        const Frame* getFrames() const { return this->frames; }

                        const unsigned long getSize() const{return this->size;}
                        const unsigned long getSkippedFrames() const{return this->skipped;}
                };
            }
        }
    }


#endif