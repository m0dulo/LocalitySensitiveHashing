cmake_minimum_required(VERSION 3.0.0)
project(lsh)
set(CMAKE_CXX_STANDARD 14)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
if(CMAKE_BUILD_TYPE MATCHES debug)
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -msse3 -std=c++11 -O1" )
else()
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -O3 -march=native" )
endif()
include_directories(src/include)
include_directories(src/3rd_party/Argumenet_helper)
set(SRCS src/include/dataloader.h
    src/include/utlis.h
    src/3rd_party/Argumenet_helper/Argument_helper.h
    src/main.cpp)
add_executable(lsh ${SRCS})
