/**
 * @file 
 * ErrorUtils is a wrapper to let you retireve the last error occurred which is saved into
 * 
 *      errno, on a linux kernel
 *      GetLastError(), on windows kernel
 * 
 * This wrapper provides a unqiue defined macro as a cross-platform one
 * 
 * @date 2023-05-20
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef ERROR_UTILS_JPL
#define ERROR_UTILS_JPL

    #include <string>

    #ifdef _WIN32
        #include <errhandlingapi.h>
        #include <windows.h> //For LocalFree
    #endif

    #ifdef __linux__
        #include <errno.h>
        #include <string.h>//Only for strerror

        namespace jpl{
            namespace _utils{
                namespace _error{

                    /**
                     * @return the error code of the last occurred one
                     */
                    unsigned int _GetLastError(){return errno;}

                    std::string _GetLastErrorAsString(unsigned int _error_code){return std::string(strerror(_error_code));}
                    /**
                     * @return the description of the last error occurred
                     */
                    std::string _GetLastErrorAsString(){ return _GetLastErrorAsString(_GetLastError()); }
                }
            }
        }

    #elif _WIN32

        namespace jpl{
            namespace _utils{
                namespace _error{
                    
                    unsigned int _GetLastError(){return GetLastError();}

                    std::string _GetLastErrorAsString(DWORD errorMessageID)
                    {   
                        LPSTR messageBuffer = nullptr;

                        size_t size = FormatMessageA(
                                    
                                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                    NULL, 
                                    errorMessageID, 
                                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                                    (LPSTR)&messageBuffer, 0, NULL
                        );
                        
                        std::string message(messageBuffer, size);

                        LocalFree(messageBuffer);
                                
                        return message;
                    }

                    std::string _GetLastErrorAsString(){return _GetLastErrorAsString(_GetLastError());}
                }
            }
        }

    #endif

#endif