cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

# PkgConfig
include(FindPkgConfig)

# cairo
pkg_check_modules(CAIRO cairo)

if(NOT CAIRO_FOUND)
    message(FATAL_ERROR "Cairo not found!")
else()
    message(STATUS "Cairo library status:")
    message(STATUS "    version: ${CAIRO_VERSION}")
    message(STATUS "    include path: ${CAIRO_INCLUDE_DIRS}")
    message(STATUS "    lib path: ${CAIRO_LIBDIR}")
    message(STATUS "    libraries: ${CAIRO_LIBRARIES}")
endif()

# Project
project(cairorustbugreproduce)

file(GLOB_RECURSE SRC_LIST
    ./src/*.c
    ./src/*.h
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC ${CAIRO_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${CAIRO_LIBDIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CAIRO_LIBRARIES})
