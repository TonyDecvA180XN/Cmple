# Set minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Configure basic project settings: name, PL, 
project(Cmple LANGUAGES C CXX)

# Add OpenGL dependency (required for OpenGL apps)
find_package(OpenGL REQUIRED)

# Declare C++ source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Source/main.cpp)

# Import glfw library
add_subdirectory(ThirdParty/glfw)

# Declare C++ header folders
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/Include
    ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/include
)

# Declare C++ link folders
target_link_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/src
)

# Set C++17 standard requirement
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL::GL)
