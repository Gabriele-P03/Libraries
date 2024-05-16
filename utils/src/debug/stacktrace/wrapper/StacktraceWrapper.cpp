#include "StacktraceWrapper.hpp"

jpl::_utils::_collections::_list::LinkedList<jpl::_utils::_debug::Frame*>* jpl::_utils::_debug::queryStacktrace(unsigned int skipped, unsigned int maxSize){

    #ifdef __linux__
                    jpl::_utils::_collections::_list::LinkedList<Frame*> *frames = new jpl::_utils::_collections::_list::LinkedList<Frame*>();
                    void* buffer[maxSize];
                    //Retrieve the stacktrace 
                    int size = backtrace(buffer, maxSize);
                    //Translate symbols
                    char** c_c_buffer = backtrace_symbols(buffer, size);
                    //If it could not translate them, the vector is filled with size invalid frame
                    if(c_c_buffer == NULL){
                        for(size_t i = 0; i < size; i++)
                            frames->add(new Frame());
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
                            frames->add(new jpl::_utils::_debug::Frame(line, func_name, address, file_name));
                        }
                    }
                    return frames;
    #elif _WIN32
                    jpl::_utils::_collections::_list::LinkedList<Frame*>* frames = new jpl::_utils::_collections::_list::LinkedList<Frame*>();

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
                                    Frame* frame = new Frame(line.LineNumber-1, std::string(pSymbol->Name), std::to_string(pSymbol->Address), std::string(line.FileName));
                                    frames->add(frame);
                                    continue;
                                }
                            }

                            frames->add(new Frame());
                        }
                        SymCleanup(process);

                        //Let's remove skipped frames
                        if(frames->getSize()-skipped > 0){
                            for(size_t i = 0; i < skipped; i++){
                                frames->removeAt(i);
                            }
                        }

                    }
                    return frames;
                
    #endif
}