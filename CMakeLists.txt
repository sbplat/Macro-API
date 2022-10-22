cmake_minimum_required(VERSION 3.22)

project(
    MACRO
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" ON)
option(MACRO_INSTALL "Generate the install target" ON)

set(MACRO_LIBRARY_TYPE
    "${MACRO_LIBRARY_TYPE}"
    CACHE STRING "Library type override (STATIC, SHARED, or leave empty for BUILD_SHARED_LIBS)"
)

if(MACRO_LIBRARY_TYPE)
    if(NOT MACRO_LIBRARY_TYPE STREQUAL "SHARED" AND NOT MACRO_LIBRARY_TYPE STREQUAL "STATIC")
        set(MACRO_LIBRARY_TYPE "${BUILD_SHARED_LIBS}")
    endif()
else()
    if(BUILD_SHARED_LIBS)
        set(MACRO_LIBRARY_TYPE "SHARED")
    else()
        set(MACRO_LIBRARY_TYPE "STATIC")
    endif()
endif()

if(NOT WIN32)
    find_package(Threads REQUIRED)
endif()

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

if(BUILD_DOCS)
    # todo
endif()
