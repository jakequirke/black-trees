cmake_minimum_required(VERSION 3.10)
project(jrpg_cpp_starter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(CORE_DIR "${CMAKE_SOURCE_DIR}/core")
set(ENT_DIR "${CMAKE_SOURCE_DIR}/entities")

# Collect files
file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/*.cpp"
    "${CORE_DIR}/*.cpp"
    "${ENT_DIR}/*.cpp"
)

add_executable(jrpg_demo ${SRC_FILES})

# Make the include root be project root so we can include like "entities/Player.h"
target_include_directories(jrpg_demo PRIVATE "${CMAKE_SOURCE_DIR}")

# Compiler warnings
if(MSVC)
    target_compile_options(jrpg_demo PRIVATE /W4 /permissive-)
else()
    target_compile_options(jrpg_demo PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()
