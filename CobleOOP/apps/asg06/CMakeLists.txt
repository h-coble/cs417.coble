cmake_minimum_required(VERSION 3.1)

#set the project name
project(rope)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

#add the executable

add_executable(logger loggerTest.cpp)
add_executable(factory factoryTest.cpp)




