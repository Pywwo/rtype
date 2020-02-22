cmake_minimum_required(VERSION 3.11)

project(ecs)

file(
        GLOB_RECURSE
        SOURCES_CPP
        sources/*.cpp
)
file(
        GLOB_RECURSE
        SOURCES_HPP
        include/*.hpp
)

add_library(ecs ${SOURCES_CPP} ${SOURCES_HPP})
target_include_directories(
        ecs
        PUBLIC
        include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
