cmake_minimum_required(VERSION 3.11)

project(collisionsystem)

file(
        GLOB_RECURSE
        SOURCES_CPP
        *.cpp
)
file(
        GLOB_RECURSE
        SOURCES_HPP
        *.hpp
)
file(
        GLOB_RECURSE
        COMMONS_CPP
        ../../commons/*.cpp
)
file(
        GLOB_RECURSE
        COMMONS_HPP
        ../../commons/*.hpp
)
file(
        GLOB_RECURSE
        SERVER_CPP
        ../../server/*.cpp
)
file(
        GLOB_RECURSE
        SERVER_HPP
        ../../server/*.hpp
)

add_library(
        collision_system
        SHARED
        ${SOURCES_CPP}
        ${SOURCES_HPP}
        ${COMMONS_CPP}
        ${COMMONS_HPP}
        ${SERVER_CPP}
        ${SERVER_HPP}
)

target_link_libraries(collision_system ecs)

target_include_directories(
        collision_system PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ../../commons
        ../../commons/dl
        ../../commons/components
        ../../commons/exception
        ../../commons/network
        ../../commons/network/udpsocket
        ../../commons/network/datagram
        ../../commons/other
        ../../lib/ecs/include
        ../../server/include
        ../../server/interface
)

add_custom_command(TARGET collision_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:collision_system> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib
)