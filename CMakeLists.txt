project(rtype)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
    add_definitions("-fPIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wuninitialized -Wunreachable-code")
endif (UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
endif (APPLE)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/ecs)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_CLIENT
        ${PROJECT_SOURCE_DIR}/client/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/client/include/*.hpp
)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_SERVER
        ${PROJECT_SOURCE_DIR}/server/sources/*.cpp
        ${PROJECT_SOURCE_DIR}/server/include/*.hpp
        ${PROJECT_SOURCE_DIR}/server/interface/*.hpp
)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_TESTS
        ${PROJECT_SOURCE_DIR}/tests/*.cpp
)

file(
        GLOB_RECURSE
        RTYPE_SOURCES_COMMON
        ${PROJECT_SOURCE_DIR}/commons/*.cpp
        ${PROJECT_SOURCE_DIR}/commons/*.hpp
)

add_executable(r-type_client ${RTYPE_SOURCES_CLIENT} ${RTYPE_SOURCES_COMMON})
target_include_directories(
        r-type_client PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons
        ${PROJECT_SOURCE_DIR}/commons/dl
        ${PROJECT_SOURCE_DIR}/commons/exception
        ${PROJECT_SOURCE_DIR}/commons/network
        ${PROJECT_SOURCE_DIR}/commons/network/udpsocket
        ${PROJECT_SOURCE_DIR}/commons/network/datagram
        ${PROJECT_SOURCE_DIR}/commons/other
        ${PROJECT_SOURCE_DIR}/client/include/
        ${PROJECT_SOURCE_DIR}/client/include/systems/
        ${PROJECT_SOURCE_DIR}/client/include/components/
        ${PROJECT_SOURCE_DIR}/lib/ecs/include
)

target_link_libraries(
        r-type_client
        ecs
        ${CONAN_LIBS}
)

add_executable(r-type_server ${RTYPE_SOURCES_SERVER} ${RTYPE_SOURCES_COMMON})
target_include_directories(
        r-type_server PUBLIC
        ${CMAKE_INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/commons
        ${PROJECT_SOURCE_DIR}/commons/exception
        ${PROJECT_SOURCE_DIR}/server/sources
        ${PROJECT_SOURCE_DIR}/server/components
        ${PROJECT_SOURCE_DIR}/server/include
        ${PROJECT_SOURCE_DIR}/server/interface
        ${PROJECT_SOURCE_DIR}/commons/network
        ${PROJECT_SOURCE_DIR}/commons/network/udpsocket
        ${PROJECT_SOURCE_DIR}/commons/network/datagram
        ${PROJECT_SOURCE_DIR}/lib/ecs/include/
)

target_link_libraries(
        r-type_server
        ecs
        ${CONAN_LIBS}
)

if (UNIX)
    add_executable(r-type_tests ${RTYPE_SOURCES_TESTS} ${RTYPE_SOURCES_COMMON})

    target_include_directories(
            r-type_tests PUBLIC
            ${CMAKE_INCLUDE_PATH}
            ${PROJECT_SOURCE_DIR}/commons
            ${PROJECT_SOURCE_DIR}/commons/dl
            ${PROJECT_SOURCE_DIR}/commons/exception
            ${PROJECT_SOURCE_DIR}/commons/network
            ${PROJECT_SOURCE_DIR}/commons/network/udpsocket
            ${PROJECT_SOURCE_DIR}/commons/network/datagram
            ${PROJECT_SOURCE_DIR}/commons/other
            ${PROJECT_SOURCE_DIR}/client/include/
            ${PROJECT_SOURCE_DIR}/client/include/systems/
            ${PROJECT_SOURCE_DIR}/client/include/components/
            ${PROJECT_SOURCE_DIR}/lib/ecs/include
    )

    target_link_libraries(
            r-type_tests
            criterion
            ecs
    )

endif (UNIX)

target_link_libraries(
        ecs
)

file(GLOB BUILD_DEPENDENCY "build_dependency/*")


file(COPY ${BUILD_DEPENDENCY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(./dynamic_libraries/CMakeLists.txt)
