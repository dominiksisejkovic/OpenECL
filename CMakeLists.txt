cmake_minimum_required(VERSION 3.15)
project(OPEN_ECL)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Load all files
file(GLOB_RECURSE OPEN_ECL_SOURCES "src/*.cpp")
file(GLOB_RECURSE OPEN_ECL_HEADERS "src/*.hpp")

set(OPEN_ECL_INCLUDE_DIRS "")
foreach (_headerFile ${OPEN_ECL_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND OPEN_ECL_INCLUDE_DIRS ${_dir})
endforeach ()

list(REMOVE_DUPLICATES OPEN_ECL_INCLUDE_DIRS)
include_directories(${OPEN_ECL_INCLUDE_DIRS})

add_executable(OPEN_ECL ${OPEN_ECL_SOURCES})
