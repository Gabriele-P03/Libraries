/**
 * A profiler can be used to catch global,current program and current thread memory consumption;
 * it can run either single-time or as a scheduled thread 
 * 
 * Usually we represents the CPU usage as a percentage of elapsed time since process started.
 * So the total CPU usage of an application is the sum of utime and stime, divided by elapsed time 
 * 
 * @date 2024-02-21
 * 
 * @author Gabriele-P03
*/

#ifndef PROFILER_JPL
#define PROFILER_JPL

    #include <ctime>
    #include "../StringUtils.hpp"
    #include <stdio.h>
    #include <string.h>

    #ifdef _WIN32
        #define MEMORY_CONSUMPTION_ARRAY_SIZE_PROFILE_JPL 4
    #elif __linux__
        #include <sys/sysinfo.h>
        #define MEMORY_CONSUMPTION_ARRAY_SIZE_PROFILE_JPL 5 //The first element contains seconds since boot
    #endif

    namespace jpl{
        namespace _utils{
            namespace _profiler{

                struct SystemInfo{

                    unsigned long time;         //Time as the SystemInfo stuct has been created at
                    unsigned long upTime;       //Seconds since boot

                    unsigned long totalMemory;  //Total RAM
                    unsigned long freeMemory;   //Free RAM at time
                    unsigned long usedMemory;   //RAM used globally
                    unsigned long procMemory;   //RAM used by the current process
                    unsigned long virtualTotalMemory;
                    unsigned long virtualFreeMemory;
                    unsigned long virtualUsedMemory;
                    unsigned long virtualProcMemory;

                    float totalCpu;     //Total Used CPU percentage 
                    unsigned long *procsCPUMhz; // Mhz of each CPU unit
                    float procCpu;      //Used CPU percentage by this process 

                    ~SystemInfo();
                };

                typedef struct sysinfo SysInfo;

                class Profiler{

                    private:

                        static unsigned long processors;    //Contains the amount of CPU unit available

                        #ifdef __linux__
                            FILE* procSelfStatus;
                            FILE* procLoadavg;
                            FILE* procCpuinfo;
                            FILE* procSelfStat;
                        #endif 

                        /**
                         * Parse the single line in order to retrieve what is before " Kb"  
                        */
                        virtual unsigned long parseKBLine(char* line) const;

                        /**
                         * It probes global and local (this proc) memory consumption such as
                         * total memory, total used memory, free one and used one by this proc
                        */
                        virtual void measureMemory(SystemInfo* &systemInfo) const;

                        /**
                         * It probes global and local (this proc) cpu consumption such as
                         * total cpu percentage, Mhz of each unit and percentage of this proc
                        */
                        virtual void measureCpu(SystemInfo* &systemInfo) const;

                        virtual void init();

                    public:

                        Profiler();
                        ~Profiler();

                        const SystemInfo* const measure() const;
                };



            }
        }
    }

#endif