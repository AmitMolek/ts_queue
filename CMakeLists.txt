cmake_minimum_required(VERSION 3.0)  # CMake version check
project(ts_queue)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES test/main.cpp test/ts_queue_tests.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include/)
target_include_directories(${PROJECT_NAME} PRIVATE lib/)