cmake_minimum_required(VERSION 3.15)

project(DirInspect LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
add_executable(DirInspect
    src/main.cpp
)

# Platform-specific settings
if (WIN32)
    message(STATUS "Target platform: Windows")
    target_compile_definitions(DirInspect PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    message(STATUS "Target platform: Linux/Unix")
    target_compile_definitions(DirInspect PRIVATE PLATFORM_LINUX)
endif()
