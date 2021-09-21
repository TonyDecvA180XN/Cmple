# Set minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Configure basic project settings: name, PL, 
project(Cmple LANGUAGES C CXX)

# Add OpenGL dependency (required for OpenGL apps)
find_package(OpenGL REQUIRED)

# Declare C++ source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Source/main.cpp)

# Set C++17 standard requirement
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Import libraries
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glad)

# Declare C++ header folders
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/Include
    ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/include
    ${PROJECT_SOURCE_DIR}/ThirdParty/glad/include
)    

# Declare C++ link folders
target_link_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/ThirdParty/glfw
    ${PROJECT_SOURCE_DIR}/ThirdParty/glad
)    

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    OpenGL::GL
    glfw
    glad
)
