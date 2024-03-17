cmake_minimum_required(VERSION 3.9)

set(UTILS_VERSION_JPL, "1.0.0")
set(UTILS_VERSION_JPL_str, "1_0_0")
project(Utils VERSION ${UTILS_VERSION_JPL})
message("Compiling Utils Module v: " + ${UTILS_VERSION_JPL})

#Utils's MACRO part
if(${PROFILER_JPL})
    add_library( utilsJPL_sh SHARED "src/debug/Profiler.cpp" "src/StringUtils.cpp")
    set_target_properties(utilsJPL_sh PROPERTIES OUTPUT_NAME "utilsJPL_1_0_0")
    add_library( utilsJPL_st STATIC "src/debug/Profiler.cpp" "src/Logger.cpp")
    set_target_properties(utilsJPL_st PROPERTIES OUTPUT_NAME "utilsJPL_1_0_0")
    message("Module: Utils ")
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