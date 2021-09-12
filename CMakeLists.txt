# Set minimum CMake version requirement
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# Configure basic project settings: name, PL, 
PROJECT(Cmple LANGUAGES C CXX)

# Declare C++ source files
ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Source/main.cpp)

# Declare C++ header files
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

# Set C++17 standard requirement
TARGET_COMPILE_FEATURES(${PROJECT_NAME} PUBLIC cxx_std_17)
