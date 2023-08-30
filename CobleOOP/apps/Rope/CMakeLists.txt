cmake_minimum_required(VERSION 3.1)

#set the project name
project(hanoi)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

#add the executable
add_executable(indexCardsTestDriver indexCardsTestDriver.cpp)

add_executable(indexCards indexCards.cpp)

#Test code for treeDemo from CS 372
add_executable(main main.cpp)


