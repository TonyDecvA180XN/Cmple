# Set minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Configure basic project settings: name, PL, 
project(Cmple LANGUAGES C CXX)

# Declare C++ source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Source/main.cpp)

# Declare C++ header files
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

# Set C++17 standard requirement
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
