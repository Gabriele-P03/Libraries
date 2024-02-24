/**
 * A profiler can be used to catch global,current program and current thread memory consumption;
 * it can run either single-time or as a scheduled thread 
 * 
 * 
 * @date 2024-02-21
 * 
 * @author Gabriele-P03
*/

#ifndef PROFILER_JPL
#define PROFILER_JPL

    #include <ctime>

    #ifdef _WIN32
        
    #elif __linux__
        #include <sys/sysinfo.h>


    #endif

    namespace jpl{
        namespace _utils{
            namespace _profiler{

                struct SystemInfo{

                    unsigned long time;     //Time as the SystemInfo stuct has been created at
                    unsigned long upTime;   //Seconds since boot

                    unsigned long totalRam; //Total RAM
                    unsigned long freeRam;  //Free RAM at time
                    unsigned long procRam;  //RAM used by the current process
                    unsigned long threadRam;//RAM used by the thread which created this struct

                    unsigned long totalCpu; //Total Used CPU percentage 
                    unsigned long procCpu;  //Used CPU percentage by this process 
                    unsigned long threadCpu;//Used CPU percentage by this thread
                    
                };

                #ifdef _WIN32
                    
                #elif __linux__
                    typedef struct sysinfo SysInfo;

                    SystemInfo* getCurrentInfo(){
                        SysInfo memInfo;
                        sysinfo(&memInfo);

                        SystemInfo* m = new SystemInfo;
                        m->upTime = memInfo.uptime;
                        m->time = time(NULL);
                        m->totalRam = memInfo.totalram;
                        m->freeRam = memInfo.freeram;

                        return m;
                    }

                #endif

            }
        }
    }

#endif