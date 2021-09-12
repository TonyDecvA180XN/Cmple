# Set minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Setup vcpkg script with CMake (note: should be placed before project() call)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# Configure basic project settings: name, PL, 
project(Cmple LANGUAGES C CXX)

# Install fmt library
find_package(fmt REQUIRED)

# Declare C++ source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Source/main.cpp)

# Declare C++ header files
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

# Set C++17 standard requirement
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
