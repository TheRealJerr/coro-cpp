cmake_minimum_required(VERSION 3.10)


project(coro-cpp)

# Set compiler
set(CMAKE_CXX_COMPILER "g++-12")

include_directories(include)

# C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add executable
add_executable(coro-cpp-example)

# Add source files
target_sources(coro-cpp-example PRIVATE src/main.cpp)

# no link libraries needed for this example

# Set output directory
set_target_properties(coro-cpp-example PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
