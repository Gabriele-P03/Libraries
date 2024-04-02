cmake_minimum_required(VERSION 3.9)

set(EXCEPTION_VERSION_JPL "1.0.0")
set(EXCEPTION_VERSION_JPL_str "1_0_0")
project(Exception VERSION ${EXCEPTION_VERSION_JPL})
message("Compiling Exception v: " ${EXCEPTION_VERSION_JPL})

file(WRITE main.cpp "int main(){return 0;}")
add_library(Exception_st STATIC main.cpp)
add_library(Exception_sh SHARED main.cpp)
target_include_directories(Exception_st PUBLIC "src/**.hpp")
target_include_directories(Exception_sh PUBLIC "src/**.hpp")

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


include_directories(CPLUS_INCLUDE_PATH)
include_directories(C_INCLUDE_PATH)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)