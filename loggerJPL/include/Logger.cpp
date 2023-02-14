#include "Logger.hpp"

const jpl::logger::LOG_STATUS jpl::logger::OK = "OK";
const jpl::logger::LOG_STATUS jpl::logger::WARNING = "WARNING";
const jpl::logger::LOG_STATUS jpl::logger::ERR = "ERROR";

jpl::logger::Logger* jpl::logger::Logger::INSTANCE = new jpl::logger::Logger(jpl::logger::Logger::getStandardPathToFile()); 

jpl::logger::Logger::Logger(std::string pathToFile){

    this->file = new std::fstream();
    this->file->open(pathToFile, std::ios_base::out);

    if(!file){
        //As I said in the doc into Logger header file
        std::cout<<"Could not create log file";

        /**
         * Since it has not been possible to create the output file,
         * we need to undefine the USE_LOGGER_JPL macro in order to 
         * warn every class customers to not use anymore the Logger
         */
        #undef USE_LOGGER_JPL
    }
}

void jpl::logger::Logger::print(std::string msg){

    this->print(msg, jpl::logger::OK);
}

void jpl::logger::Logger::print(std::string msg, jpl::logger::LOG_STATUS status){

    msg = "[ " + this->getFileNameOfInstance() + " -> " + status + " ]: " + msg + "\n";
    this->file->write(msg.c_str(), msg.size());
    this->file->flush();

    std::cout<<msg;

    if(status == jpl::logger::ERR){
        
    }
}

void jpl::logger::Logger::closeLogger(){

    this->print("Logger closed");
    this->file->close();
}








std::string jpl::logger::Logger::getFileNameOfInstance(){

    std::tm *ltm = jpl::logger::Logger::getTM();

    return  std::to_string((*ltm).tm_mday) + "-" + 
            std::to_string((*ltm).tm_mon+1) + "-" + 
            std::to_string((*ltm).tm_year + 1900) + "_" +
            std::to_string((*ltm).tm_hour) + "-" +
            std::to_string((*ltm).tm_min) + "-" +
            std::to_string((*ltm).tm_sec);
}


std::string jpl::logger::Logger::getStandardPathToFile(){
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

    pathToFile += "/logs/" + jpl::logger::Logger::getFileNameOfInstance();
    return pathToFile;
}