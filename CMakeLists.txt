project(haxer)
cmake_minimum_required(VERSION 3.1.0)

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_FLAGS "-std=c++11 -lssl -lcrypto -lpthread -lzmq" ${CMAKE_CXX_FLAGS})

message(STATUS "compiler flags :  ${CMAKE_CXX_FLAGS}")
add_subdirectory(src/haxer)
