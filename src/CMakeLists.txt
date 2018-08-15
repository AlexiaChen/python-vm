cmake_minimum_required(VERSION 2.8)

PROJECT(RAILGUN)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

ADD_EXECUTABLE(railgun main.cpp
    object/hiInteger.cpp
    object/hiString.cpp
    object/hiObject.cpp
    util/arrayList.cpp
    util/map.cpp
    runtime/interpreter.cpp
    runtime/universe.cpp
    code/binaryFileParser.cpp
    code/codeObject.cpp)
    
INCLUDE_DIRECTORIES(./)
