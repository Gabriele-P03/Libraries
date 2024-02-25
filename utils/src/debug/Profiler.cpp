#include "Profiler.hpp"

unsigned long jpl::_utils::_profiler::Profiler::processors;
jpl::_utils::_profiler::SystemInfo::~SystemInfo(){
    delete[] this->procsCPUMhz;
}

jpl::_utils::_profiler::Profiler::Profiler(){
    this->init();
}

void jpl::_utils::_profiler::Profiler::init(){
    #ifdef __linux__
        this->procSelfStatFile = fopen("/proc/self/status", "r");
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
        while (fgets(buffer, 128, this->procSelfStatFile) != NULL)
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
            char *p = buffer;
            while( p[i++] != ' ' ){}
            buffer[i-1] = '\0';
            systemInfo->totalCpu = atof(buffer)*100/jpl::_utils::_profiler::Profiler::processors;
        }
        delete[] buffer;

        /*
            READING PERCENTAGE OF USED CPU BY THIS PROCESSOR
        */
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

jpl::_utils::_profiler::Profiler::~Profiler(){
    #ifdef __linux__
        fclose(this->procCpuinfo);
        fclose(this->procLoadavg);
        fclose(this->procSelfStatFile);
    #endif
}