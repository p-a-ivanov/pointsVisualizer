cmake_minimum_required(VERSION 3.0.0)
project(checkPoints VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SOURCES
    headers/includes.h
    headers/point.h
    headers/func.h
    sources/point.cpp
    sources/func.cpp)

add_executable(checkPoints main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
