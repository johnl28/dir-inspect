cmake_minimum_required(VERSION 3.15)

project(DirInspect LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
add_executable(DirInspect
    src/main.cpp
    src/DirInspect.cpp
)



target_include_directories(DirInspect PRIVATE ${CMAKE_SOURCE_DIR}/lib)
