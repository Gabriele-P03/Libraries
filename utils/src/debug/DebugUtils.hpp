/**
 * In this header file there is only a function which can be used to check if a debugger is 
 * attached to the program
 * 
 * @file
 *
 * @date 2023-05-26
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef DEBUG_UTILS_JPL
#define DEBUG_UTILS_JPL

    #include "ErrorUtils.hpp"//Used to catch errors during reading status
    #include <jpl/exception/runtime/RuntimeException.hpp>

    #ifdef _WIN32
        #include <debugapi.h>
    #endif
    #ifdef __linux__
        #include <fcntl.h>
        #include <unistd.h>
    #endif

    namespace jpl{
        namespace _utils{
            namespace _debug{

                #ifdef __linux__

                    /**
                     * @return if the process which called this function has debugger attached on
                     */
                    inline bool isDebugging(){
                        const int fd = open("/proc/self/status", O_RDONLY);
                        if(fd == -1){
                            std::string cause = std::string("Could not open self-status: ");
                            cause += jpl::_utils::_error::_GetLastErrorAsString();
                            throw new _exception::RuntimeException(cause.c_str());
                        }

                        char buffer[4096];
                        const unsigned int read_byte = read(fd, buffer, sizeof(buffer)-1);

                        if(read_byte <= 0){
                            std::string cause = std::string("Could not read self-status fully: ");
                            cause += jpl::_utils::_error::_GetLastErrorAsString();
                            throw new _exception::RuntimeException(cause.c_str());
                        }

                        buffer[read_byte] = '\0';
                        constexpr char tracePIDString[] = "TracerPid:";
                        const auto ptr = strstr(buffer, tracePIDString);

                        if(!ptr){
                            throw new _exception::RuntimeException("No occurrence of TracerPID found into self-status");
                        }

                        for (const char* characterPtr = ptr + sizeof(tracePIDString) - 1; characterPtr <= buffer + read_byte; ++characterPtr){
                            if (isspace(*characterPtr))
                                continue;
                            else
                                return isdigit(*characterPtr) != 0 && *characterPtr != '0';
                        }

                        return false;
                    }
                    
                #elif _WIN32
                    inline bool isDebugging(){
                        return IsDebuggerPresent();
                    }
                #endif
            }
        }
    }

#endif