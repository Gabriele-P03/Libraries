cmake_minimum_required(VERSION 3.9)

set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)
set(UTILS_VERSION_JPL "1.0.0")
set(UTILS_VERSION_JPL_str "1_0_0")
project(Utils VERSION ${UTILS_VERSION_JPL})
message("Compiling Utils v: " ${UTILS_VERSION_JPL})

set(FIRST_CALL_ADD_LIBRARY_SH TRUE)
set(FIRST_CALL_ADD_LIBRARY_ST TRUE)

function (addSRC PATH_SRC NAME_INFO STATIC_ENABLE SHARED_ENABLE)


    if(${STATIC_ENABLE})
        if(${FIRST_CALL_ADD_LIBRARY_SH})
            add_library( utilsJPL_sh SHARED ${PATH_SRC})
            set_target_properties(utilsJPL_sh PROPERTIES OUTPUT_NAME "utilsJPL_1_0_0")
            set(FIRST_CALL_ADD_LIBRARY_SH FALSE PARENT_SCOPE)#CACHE BOOL "First Call to Add Library for Shared done")
        else()
            target_sources(utilsJPL_sh PUBLIC ${PATH_SRC})    
        endif()
    endif()    

    if(${SHARED_ENABLE})
        if(${FIRST_CALL_ADD_LIBRARY_ST})
            add_library( utilsJPL_st STATIC ${PATH_SRC})
            set_target_properties(utilsJPL_st PROPERTIES OUTPUT_NAME "utilsJPL_1_0_0")
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

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


include_directories(CPLUS_INCLUDE_PATH)
include_directories(C_INCLUDE_PATH)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)