# Set directory paths
set(CORE_INCLUDE ${PROJECT_SOURCE_DIR}/Core/Include)
set(CORE_SOURCE ${PROJECT_SOURCE_DIR}/Core/Source)

# Setup source code grab from specified firectories
file(GLOB ${PROJECT_CORE_NAME}_SOURCE_FILES CONFIGURE_DEPENDS ${CORE_SOURCE}/*.cpp)

# Define core library and runtime launcher
add_executable(${PROJECT_NAME} ${CORE_SOURCE}/main.cpp)
add_library(${PROJECT_CORE_NAME} ${${PROJECT_CORE_NAME}_SOURCE_FILES})

# Set compile requirements
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_CORE_NAME} PUBLIC cxx_std_17)

# Set include paths
target_include_directories(${PROJECT_NAME} PUBLIC ${CORE_INCLUDE})
target_include_directories(${PROJECT_CORE_NAME} PUBLIC
    ${CORE_INCLUDE}
    ThirdParty/glfw/include
    ThirdParty/glad/include
)

# Set linker paths
target_link_directories(${PROJECT_CORE_NAME} PUBLIC
    ThirdParty/glfw
    ThirdParty/glad
)

# Link core and runtime launcher
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${PROJECT_CORE_NAME}
    glfw
    glad
)
