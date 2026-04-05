cmake_minimum_required(VERSION 3.16)
project(MyEngine C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Build options
option(BUILD_SANDBOX "Build the sandbox/test app" ON)

# Dependencies
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

# Your engine library
add_subdirectory(Engine)

# Your game/sandbox
if(BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif()

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE vendor/glm)
