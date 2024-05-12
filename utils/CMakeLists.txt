cmake_minimum_required(VERSION 3.9)
message("")
message("---------------------------------------- UTILS ----------------------------------------")
message("")
set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)
set(UTILS_VERSION_JPL "1.0.0")
project(UTILS VERSION ${UTILS_VERSION_JPL})
message("Compiling Utils v: " ${UTILS_VERSION_JPL})

set(FIRST_CALL_ADD_LIBRARY_SH TRUE)
set(FIRST_CALL_ADD_LIBRARY_ST TRUE)
set(STRING_UTILS_CPP TRUE)

if(${USE_STACKTRACE_W_EXCEPTION_JPL})
    add_compile_definitions(USE_STACKTRACE_W_EXCEPTION_JPL)
    message(STATUS " MACRO: Exception with Stacktrace have been enabled")
    if(${AUTO_LOG_EXCEPTION_JPL})
        add_compile_definitions(AUTO_LOG_EXCEPTION_JPL)
        message(STATUS " MACRO: Stacktrace auto-logged after exception has been enabled")
    endif()
    if(!${STACKTRACE_JPL})
        message(STATUS "Stacktrace auto-enabled")
        set(STACKTRACE_JPL TRUE CACHE BOOL "Exception needs Stacktrace ")
    endif()
endif()

function (addSRC PATH_SRC NAME_INFO STATIC_ENABLE SHARED_ENABLE)


    if(${STATIC_ENABLE})
        if(${FIRST_CALL_ADD_LIBRARY_SH})
            add_library( utilsJPL_sh SHARED ${PATH_SRC})
            set_target_properties(utilsJPL_sh PROPERTIES OUTPUT_NAME "utilsJPL" SOVERSION ${UTILS_VERSION_JPL})
            set(FIRST_CALL_ADD_LIBRARY_SH FALSE PARENT_SCOPE)#CACHE BOOL "First Call to Add Library for Shared done")
        else()
            target_sources(utilsJPL_sh PUBLIC ${PATH_SRC})    
        endif()
    endif()    

    if(${SHARED_ENABLE})
        if(${FIRST_CALL_ADD_LIBRARY_ST})
            add_library( utilsJPL_st STATIC ${PATH_SRC})
            set_target_properties(utilsJPL_st PROPERTIES OUTPUT_NAME "utilsJPL")
            set(FIRST_CALL_ADD_LIBRARY_ST FALSE PARENT_SCOPE)#CACHE BOOL "First Call to Add Library for Static done")
        else()
            target_sources(utilsJPL_st PUBLIC ${PATH_SRC})
        endif()
    endif()

    message("-- Adding " ${NAME_INFO} "... ")

endfunction()


#Utils's MACRO part
if(${PROFILER_JPL})
    addSRC("src/debug/Profiler.cpp" "Profiler" TRUE TRUE)
    set(STRING_UTILS_CPP TRUE CACHE BOOL "Profiler needs StringUtils")
endif()
if(${STRING_UTILS_CPP})
    addSRC("src/StringUtils.cpp" "StringUtils" TRUE TRUE)
endif()
if(${STACKTRACE_JPL})
    addSRC("src/debug/stracktrace/wrapper/StacktraceWrapper.cpp" "StacktraceWrapper" TRUE TRUE)
endif()

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


include_directories(CPLUS_INCLUDE_PATH)
include_directories(C_INCLUDE_PATH)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)