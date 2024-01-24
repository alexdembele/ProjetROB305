cmake_minimum_required(VERSION 3.14)

# ----------------------------------------------------------------------------- #
# Project name                                                                  #
# ----------------------------------------------------------------------------- #

project(ROB305)

# ----------------------------------------------------------------------------- #
# C++ standard                                                                  #
# ----------------------------------------------------------------------------- #

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_FLAGS "-Wall" "-lrt")

# ----------------------------------------------------------------------------- #
# Header                                                                 #
# ----------------------------------------------------------------------------- #
include_directories(inc)

file(GLOB_RECURSE SRC_FILES CMAKE_CONFIGURE_DEPENDS
"src/*.cpp"
"src/*.c")

add_executable(ROB305 ${SRC_FILES})

set_target_properties(mon_executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}../build
)