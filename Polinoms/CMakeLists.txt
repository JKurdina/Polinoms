cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(Polinoms)

include(function.cmake)

add_subdirectory(MyLibrary)
add_subdirectory(Polinoms)


option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()

