cmake_minimum_required(VERSION 3.9)

project(LoggerJPL VERSION 1.0.0)

add_library( loggerJPL_sh SHARED "src/Logger.cpp")
set_target_properties(loggerJPL_sh PROPERTIES OUTPUT_NAME "loggerJPL_1_0_0")
add_library( loggerJPL_st STATIC "src/Logger.cpp")
set_target_properties(loggerJPL_st PROPERTIES OUTPUT_NAME "loggerJPL_1_0_0")

#Both kernel options compilers cannot be decommented both at the same time

#For Linux
#set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/g++)

#For Windows
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


include_directories(CPLUS_INCLUDE_PATH)
include_directories(C_INCLUDE_PATH)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)