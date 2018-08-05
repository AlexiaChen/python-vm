cmake_minimum_required(VERSION 2.8)

PROJECT(RAILGUN)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

ADD_EXECUTABLE(railgun main.cpp
    object/hiInteger.cpp
    object/hiString.cpp
    util/arrayList.cpp
    runtime/interpreter.cpp
    code/binaryFileParser.cpp
    code/codeObject.cpp)
    
INCLUDE_DIRECTORIES(./)
