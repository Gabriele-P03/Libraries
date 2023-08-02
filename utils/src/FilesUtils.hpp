/**
 * This header file contains some functions about reading file, getting path (absolute, relative and root one)
 * and getting file
 * 
 * @date 2023-02-06
 * @copyright Copyright (c) 2023
 * @author Gabriele-P03
 */

#ifndef FILES_HPP
#define FILES_HPP

    #include <fstream>
    #include <iostream>
    #include <filesystem>

    #ifdef _WIN32
    #include <windows.h>
    #endif

    #ifdef __linux__
        #include <libgen.h> //For dirname()
        #include <unistd.h> //For readlink()
        #include <linux/limits.h> //For MAX_PATH
    #endif

    #include <jpl/utils/debug/ErrorUtils.hpp>
    #include <jpl/exception/runtime/FileNotFoundException.hpp>
    #include <jpl/exception/runtime/RuntimeException.hpp>
    #include <jpl/exception/runtime/PermissionException.hpp>
    #include <jpl/exception/runtime/IllegalArgumentException.hpp>

    namespace jpl{

        namespace _utils{

            namespace _files{

                /**
                 * @return absolute path of your root folder (i.e. where the program is located)
                 */ 
                inline std::string getRootPath() noexcept{
                    
                    std::string pathToFile = "";

                    //If the os is linux
                    #ifdef __linux__
                        char path[PATH_MAX];
                        ssize_t result = ::readlink("/proc/self/exe", path, sizeof(path)-1);
                        if(result != -1){
                            path[result] = '\0';
                            pathToFile = dirname(path);
                        }

                    #elif _WIN32
                        char path[PATH_MAX];

                        //When NULL is passed, directory of the exe is returned
                        HMODULE hmodule = GetModuleHandle(NULL);
                        if(hmodule != NULL){
                            GetModuleFileName(hmodule, path, sizeof(path));
                        }
                        pathToFile = path;
                        pathToFile = pathToFile.substr(0, pathToFile.find_last_of('\\'));
                    #else
                        #warning "Unrecognized O.S."
                    #endif

                    return pathToFile;
                }


                /**
                 * Open a file which is contained into the root folder
                 * 
                 * @param pathToFile relative to root path
                 * @param _mode  mode
                 * @param file instance of fstream already allocated
                 * 
                 * @throw FileNotFoundException if file has not been found
                 * @throw PermissionException if a special permission has been needed to open file
                 * @throw RuntimeException for any other errors
                 */ 
                inline void getLocalFile(std::string pathToFile, std::ios_base::openmode _mode, std::fstream** file){

                    std::string path = getRootPath() + "/" + pathToFile;

                    (**file).open(path, _mode);

                    if( !(**file)){
                        unsigned int _err = _error::_GetLastError();
                        switch (_err){
                            case 2:
                                throw new FileNotFoundException(pathToFile.c_str());
                            break;

                            #ifdef __linux__
                                case 13:
                            #elif _WIN32
                                case 5:
                            #endif
                                throw new PermissionException(
                                    std::string("Permission Needed to open " + pathToFile).c_str() 
                                    );
                            break;
                            
                        default:
                            throw new RuntimeException(_error::_GetLastErrorAsString().c_str());
                        
                        }
                    }
                }


                /**
                 * Open a file which is contained in the resources folder
                 * 
                 * @param pathToFile relative to resource path (contained into root one)
                 * @param _mode  mode
                 * @param file instance of fstream already allocated
                 * 
                 * @throw FileNotFoundException if file has not been found
                 * @throw PermissionException if a special permission has been needed to open file
                 * @throw RuntimeException for any other errors
                 */ 
                inline void getInternalFile(std::string pathToFile, std::ios_base::openmode _mode, std::fstream** file){
                    getLocalFile( "resources/" + pathToFile, _mode, file);
                }


                /**
                 * @param path
                 * @return the given path concatenate to the resources folder's one.
                 */ 
                inline std::string getInternalPath(std::string path) noexcept{return getRootPath() + "/resources/" + path;}
                /**
                 * @param path
                 * @return the given path concatenate to the root folder's one
                 */ 
                inline std::string getLocalPath(std::string path) noexcept{return getRootPath() + "/" + path;}


                /**
                 * Read an fstream
                 * If the whole file could not be read, buffer will contain only read bytes.
                 * In this case, buffer will be reallocated as it needs
                 * 
                 * @param file to be read
                 * @param buffer where read bytes will be stored
                 * @param _size of the buffer
                 * 
                 * @throw IllegalArgumentException if file had not been opened before have called this function
                 * @throw RuntimeException if file could not be fully read
                 */
                inline void readFile(std::fstream* file, char* &buffer, unsigned long &_size){
                    if(!file){
                        throw new IllegalArgumentException(file, "has not been opened yet");
                    }else{
                        //Store the length of the file in order to create the right sized buffer
                        file->seekg(0, file->end);
                        _size = file->tellg();
                        file->seekg(0, file->beg);

                        buffer = new char[_size];

                        //fstram#read return file without errors once it has been read successfully
                        if(file->read(buffer, _size)){
                            buffer[_size] = '\0';
                        }else{
                            throw new RuntimeException("File could not be fully read");
                            _size = file->tellg();
                            buffer = (char*)realloc(buffer, _size);
                        }
                    }
                }
                /**
                 * Read the file at the given path and store read data into buffer.
                 * buffer's size will be stored into _size
                 * 
                 * @param pathToFile 
                 * @param buffer 
                 * @param _size 
                 * 
                 * @throw FileNotFoundException if file has not been found
                 * @throw PermissionException if a special permission has been needed to open file
                 * @throw RuntimeException for any other errors
                 */
                inline void readFile(std::string pathToFile, char* &buffer, unsigned long &_size){

                    std::fstream* file = new std::fstream;
                    try{
                        getInternalFile(pathToFile, std::ios_base::in, &file);
                        readFile(file, buffer, _size);//Its IllegalArgument is implicit checked by getInternalFile
                    }catch(const _exception::AbstractException* ex){
                        throw ex;
                    }
                    if(file){
                        file->close();
                        delete file;
                    }
                }
            }       
        }
    }

#endif