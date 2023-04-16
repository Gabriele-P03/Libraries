/**
 * This is a single header file which provides some functions in order to manage reading files and get paths into your 
 * project folder
 * 
 * 
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

    #include <jpl/logger/PrintLogger.hpp>

    namespace jpl{

        namespace _files{

            /**
             * Return absolute path of your root folder (i.e. where the program is located)
             */ 
            inline std::string* getRootPath(){
                
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

                return new std::string(pathToFile);
            }


            /**
             * Open a file contained in the root folder
             * 
             * @param pathToFile 
             * @param _mode 
             * @param file to be opened
             */ 
            inline void getLocalFile(std::string pathToFile, std::ios_base::openmode __modes, std::fstream** file){

                std::string path = *getRootPath() + "/" + pathToFile;

                (**file).open(path, __modes);

                if( !(**file)){
                    jpl::print("Could not open file at: " + path + ". Error: " + std::to_string(errno), jpl::_logger::ERR);
                }
            }


            /**
             * Open a file contained in the resources folder
             * 
             * @param pathToFile 
             * @param _mode 
             * @param file to be opened
             */ 
            inline void getInternalFile(std::string pathToFile, std::ios_base::openmode _mode, std::fstream** file){
                getLocalFile( "resources/" + pathToFile, _mode, file);
            }



            /**
             * Return the given path concatenate to the resources folder's one.
             * It is been used in the GameLibraryJPL
             * 
             * e.g. 
             *  /path_to_root/resources/path
             * 
             * @param path
             */ 
            inline std::string* getInternalPath(std::string path){
                return new std::string(*getRootPath() + "/resources/" + path);
            }
            /**
             * Return the given path concatenate to the root folder's one
             * 
             * e.g. 
             *  /path_to_root/path
             * 
             * @param path
             */ 
            inline std::string* getLocalPath(std::string path){
                return new std::string(*getRootPath() + "/" + path);
            }




            /**
             ****************************
            *      READ FILE PART      *
            ****************************
            */

            /**
             * Read a fstream 
             * 
             * @param file 
             * @return stuff into file as string*
             */
            inline std::string* readFile(std::fstream* file){
                if(!file){
                    jpl::print("Could not open file...", jpl::_logger::ERR);
                    return nullptr;
                }else{

                    //Store the length of the file in order to create the right sized buffer
                    file->seekg(0, file->end);
                    unsigned int length = file->tellg();
                    file->seekg(0, file->beg);

                    char* buffer = new char[length];

                    //fstram#read return file without errors once it has been read successfully
                    if(file->read(buffer, length)){
                        buffer[length] = '\0';
                        return new std::string(buffer);
                    }else{
                        jpl::print("Error during file reading. I've read only: " + std::string(buffer), jpl::_logger::ERR);
                        return nullptr;
                    }
                }
            }

            inline std::string* readFile(std::string pathToFile){

                std::fstream* file = new std::fstream;
                getInternalFile(pathToFile, std::ios_base::in, &file);
                return readFile(file);
            }
        }       
    }

#endif