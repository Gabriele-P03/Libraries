#include "Profiler.hpp"

unsigned long jpl::_utils::_profiler::Profiler::processors;
jpl::_utils::_profiler::SystemInfo::~SystemInfo(){
    delete[] this->procsCPUMhz;
}


jpl::_utils::_profiler::Profiler::Profiler(){
    this->init();
    this->started = false;
}

void jpl::_utils::_profiler::Profiler::init(){
    #ifdef __linux__
        this->procSelfStatus = fopen("/proc/self/status", "r");
        this->procSelfStat = fopen("/proc/self/stat", "r");
        this->procLoadavg = fopen("/proc/loadavg", "r");
        this->procCpuinfo = fopen("/proc/cpuinfo", "r");
        //Let's count how many processors units are available
        char buffer[256];
        while( fgets(buffer, 256, this->procCpuinfo) != NULL ){
            if( strncmp(buffer, "processor", 9) == 0){
                jpl::_utils::_profiler::Profiler::processors++;
            }
        }
        rewind(this->procCpuinfo);  //Rewinding /proc/cpuinfo
    #endif
}

void jpl::_utils::_profiler::Profiler::measureMemory(jpl::_utils::_profiler::SystemInfo *&systemInfo) const{
    #ifdef _WIN32
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        /*DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

        systemInfo->totalMemory = memInfo.ullTotalPhys; //Total Physical Memory
        systemInfo->freeMemory = memInfo.ullAvailPhys;
        systemInfo->usedMemory = systemInfo->totalMemory - systemInfo->freeMemory;

        systemInfo->virtualTotalMemory = memInfo.ullTotalVirtual;
        systemInfo->virtualFreeMemory = memInfo.ullAvailVirtual;
        systemInfo->virtualUsedMemory = memInfo.ullTotalVirtual - memInfo.ullAvailVirtual;

        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;*/

    #elif __linux__
        SysInfo memInfo;
        sysinfo(&memInfo);
        systemInfo->upTime = memInfo.uptime;
        systemInfo->totalMemory = memInfo.totalram;
        systemInfo->freeMemory = memInfo.freeram;
        systemInfo->usedMemory = systemInfo->totalMemory - systemInfo->freeMemory;

        systemInfo->virtualTotalMemory = memInfo.totalswap * memInfo.mem_unit;
        systemInfo->virtualFreeMemory = memInfo.freeswap * memInfo.mem_unit;
        systemInfo->virtualUsedMemory = (memInfo.totalswap - memInfo.freeswap) * memInfo.mem_unit;

        char buffer[128];
        bool flagVirtual = false, flagPhisically = false;
        while (fgets(buffer, 128, this->procSelfStatus) != NULL)
        {
            if (strncmp(buffer, "VmSize:", 7) == 0)
            {
                systemInfo->virtualProcMemory = this->parseKBLine(&buffer[0]);
                flagVirtual = true;
            }
            else if (strncmp(buffer, "VmRSS:", 6) == 0)
            {
                systemInfo->procMemory = this->parseKBLine(&buffer[0]);
                flagPhisically = true;
            }
            if (flagVirtual && flagPhisically)
                break;
        }
        rewind(this->procSelfStatus);
    #endif
}

void jpl::_utils::_profiler::Profiler::measureCpu(jpl::_utils::_profiler::SystemInfo* &systemInfo) const{
    #ifdef __linux__

        /*
            READING MHZ OF EACH CPU UNIT
        */
        unsigned long sizeStr = 256, i = 0, c = 0;
        while(true){
            char* buffer = new char[sizeStr];
            c = getline(&buffer, &sizeStr, this->procCpuinfo);
            if(c == 0 || c > sizeStr){
                delete[] buffer;
                break;
            }
            if( strncmp(buffer, "cpu MHz", 7) == 0){
                char* p = &buffer[c-2];
                while( *p == '.' || (*p >= '0' && *p <= '9'))
                    p--;
                systemInfo->procsCPUMhz[i++] = atoi(p);
            }
            delete[] buffer;
        }
        rewind(this->procCpuinfo);

        /*
            READING TOTAL PERCENTAGE OF USED CPU 
        */
        i = 0;
        sizeStr = 256;
        char* buffer = new char[sizeStr];
        c = getline(&buffer, &sizeStr, this->procLoadavg);
        if(c == 0 || c > sizeStr)
            systemInfo->totalCpu = 0;
        else{
            std::string str(buffer);
            std::vector<std::string> *buffer = jpl::_utils::_string::split(str, std::regex(" "));
            systemInfo->totalCpu = atof(buffer->at(0).c_str())*100.0/jpl::_utils::_profiler::Profiler::processors;
            delete buffer;
        }
        delete[] buffer;
        rewind(this->procLoadavg);

        /*
            READING PERCENTAGE OF USED CPU BY CURRENT APPLICATION
        */
        unsigned long utime, stime, starttime, elapesdtime;
        i = 0;
        sizeStr = 512;
        char buff[sizeStr];
        if( fgets(buff, 256, this->procSelfStat) != NULL){
            //14-15-22
            std::vector<std::string>* vec = jpl::_utils::_string::split(std::string(buff), std::regex("\\((.*?)\\)| "));
            float utime = atof(vec->at(13).c_str());    //utime is the time process is running in user mode
            float stime = atof(vec->at(14).c_str());    //stime is the time process is running in kernel mode
            float perc = (utime+stime)/systemInfo->upTime;
            systemInfo->procCpu = perc;
            delete vec;
        }
        rewind(this->procSelfStat);
       
    #endif
}

unsigned long jpl::_utils::_profiler::Profiler::parseKBLine(char *line) const{
    int sizeLine = strlen(line);
    const char *p = line;
    while (*p < '0' || *p > '9') // Slide pointer 'till a digit is found
        p++;
    line[sizeLine - 3] = '\0'; //-3 since the line will over with " Kb"
    return std::stoi(p);
}

const jpl::_utils::_profiler::SystemInfo *const jpl::_utils::_profiler::Profiler::measure() const{
    SystemInfo *memInfo = new SystemInfo;
    memInfo->procsCPUMhz = new unsigned long[jpl::_utils::_profiler::Profiler::processors];
    memInfo->time = time(NULL);
    this->measureMemory(memInfo);
    this->measureCpu(memInfo);
    return memInfo;
}

void* jpl::_utils::_profiler::Profiler::measures(void* instanceProfiler){

    jpl::_utils::_profiler::Profiler* profiler = static_cast<jpl::_utils::_profiler::Profiler*>(instanceProfiler);

    if( profiler == nullptr){
        throw new jpl::_exception::IllegalArgumentException("Not a instance of Profiler class has been passed");
    }

    #ifdef _WIN32
        unsigned long ms = profiler->sleepMS;
    #elif __linux__
        unsigned long ms = profiler->sleepMS*1000;
    #endif

    std::vector<const jpl::_utils::_profiler::SystemInfo*>* list = profiler->systemInfoList;
    while (profiler->started){
        const jpl::_utils::_profiler::SystemInfo* measureInfo = profiler->measure();
        list->push_back(measureInfo);
        
        #ifdef _WIN32
            Sleep(profiler->sleepMS);
        #elif __linux__
            usleep(ms);
        #endif
    }
    
    return nullptr;
}


void jpl::_utils::_profiler::Profiler::start(unsigned long sleepMS){

    if(this->started)
        throw new jpl::_exception::IllegalStateException("This profiler has been already started");
    
    this->systemInfoList = new std::vector<const jpl::_utils::_profiler::SystemInfo*>();
    this->sleepMS = sleepMS;
    this->threadProfiler = new std::thread(&jpl::_utils::_profiler::Profiler::measures, this);
    try{
        this->threadProfiler->detach();
    }catch(const std::system_error* ex){
        throw new jpl::_exception::RuntimeException("This profiler could not be started: " + jpl::_utils::_error::_GetLastErrorAsString(ex->code));
    }
    this->started = true;
}

void jpl::_utils::_profiler::Profiler::end(){

    if(!this->started)
        throw new jpl::_exception::IllegalStateException("This profiler has been already over");
    
    this->started = false;
    free(this->threadProfiler);
}

unsigned long jpl::_utils::_profiler::Profiler::getCoresAmount() {
    return jpl::_utils::_profiler::Profiler::processors;
}

const std::vector<const jpl::_utils::_profiler::SystemInfo*>* jpl::_utils::_profiler::Profiler::getSystemInfoList() const{
    return this->systemInfoList;
}


jpl::_utils::_profiler::Profiler::~Profiler(){
    #ifdef __linux__
        fclose(this->procCpuinfo);
        fclose(this->procLoadavg);
        fclose(this->procSelfStatus);
        fclose(this->procSelfStat);
    #endif
}