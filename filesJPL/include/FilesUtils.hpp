/**
 * This is a single header file which provides you some static non-member class function useful to open a file.
 * 
 * It also provides you a function, jpl::readFile(), to read a general file into a const char* buffer, but if you wanna use that function, 
 * you have to define READ_FILE_JPL macro.
 * 
 * Since the get*File() functions are needed even by readFile(), they are not defined/declared by guards preventing
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



    /**
     * Return absolute path of your root folder.
     * It works for windows and linux 
     */ 
    std::string* getRootPath(){
        
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
     * Open a file contained in the root folder of your project
     * 
     * @param pathToFile 
     * @param _mode 
     * @param file to be opened
     */ 
    void getLocalFile(std::string pathToFile, std::ios_base::openmode __modes, std::fstream** file){

        std::string path = *getRootPath() + "/" + pathToFile;

        (**file).open(path, __modes);

        if( !(**file)){
            jpl::print("Could not open file at: " + path + ". Error: " + std::to_string(errno), jpl::ERR);
        }
    }


    /**
     * Open a file contained in the "resource" folder contained in your root folder.
     * 
     * @param pathToFile 
     * @param _mode 
     * @param file to be opened
     */ 
    void getInternalFile(std::string pathToFile, std::ios_base::openmode _mode, std::fstream** file){
        getLocalFile( "resources/" + pathToFile, _mode, file);
    }



    /**
     * Return the given path concatenate to the resources folder's one
     * 
     * e.g. 
     * path: _example -> /path/to/root/resources_folder/_example
     */ 
    std::string* getInternalPath(std::string path){
        return new std::string(*getRootPath() + "/resources/" + path);
    }
    /**
     * Return the given path concatenate to the root folder's one
     * 
     * e.g. 
     * path: _example -> /path/to/root/_example
     */ 
    std::string* getLocalPath(std::string path){
        return new std::string(*getRootPath() + "/" + path);
    }





    /**
     ****************************
    *      READ FILE PART      *
    ****************************
    */

    #ifdef READ_FILE_JPL

        std::string* readFile(std::fstream* file){
            if(!file){
                jpl::print("Could not open file...", jpl::ERR);
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
                    jpl::print("Error during file reading. I've read only: " + std::string(buffer), jpl::ERR);
                    return nullptr;
                }
            }
        }

        std::string* readFile(std::string pathToFile){

            std::fstream* file = new std::fstream;
            getInternalFile(pathToFile, std::ios_base::in, &file);
            return readFile(file);
        }

    #endif

#endif