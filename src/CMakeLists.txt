cmake_minimum_required(VERSION 2.8)

PROJECT(RAILGUN)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb -rdynamic")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -rdynamic")

ADD_EXECUTABLE(railgun main.cpp
    object/hiInteger.cpp
    object/hiDouble.cpp
    object/hiString.cpp
    object/hiObject.cpp
    object/hiList.cpp
    object/hiDict.cpp
    object/klass.cpp
    util/arrayList.cpp
    util/map.cpp
    util/handles.cpp
    runtime/interpreter.cpp
    runtime/universe.cpp
    runtime/frameObject.cpp
    runtime/functionObject.cpp
    runtime/stringTable.cpp
    runtime/module.cpp
    runtime/traceback.cpp
    runtime/generator.cpp
    runtime/cellObject.cpp
    memory/heap.cpp
    memory/oopClosure.cpp
    code/binaryFileParser.cpp
    code/codeObject.cpp)

ADD_LIBRARY(math SHARED
    extlib/math.cpp)

ADD_CUSTOM_COMMAND(TARGET math
    POST_BUILD
    COMMAND mkdir -p lib
    COMMAND cp libmath.so lib/
    COMMAND cp ../lib/*.py lib/
    COMMAND python -m compileall lib/*.py
    )
    
INCLUDE_DIRECTORIES(./)
TARGET_LINK_LIBRARIES(railgun ${CMAKE_DL_LIBS})
