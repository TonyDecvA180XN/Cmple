# Set minimum CMake vesrion allowed
cmake_minimum_required(VERSION 3.12)

# Set global constant names
set(PROJECT_NAME Cmple)
set(PROJECT_CORE_NAME ${PROJECT_NAME}Core)
set(PROJECT_TEST_NAME ${PROJECT_NAME}Test)

# Config
set(ENABLE_TESTS ON CACHE BOOL "Build tests" FORCE)

# Initiate project
project(Cmple LANGUAGES C CXX)

# Add project core
add_subdirectory(Core)

# Add 3rd party libraries
find_package(OpenGL REQUIRED)
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glad)
if (${ENABLE_TESTS})
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    add_subdirectory(ThirdParty/gtest)
endif()

# Add tests
if (${ENABLE_TESTS})
    add_subdirectory(Tests)
endif()
