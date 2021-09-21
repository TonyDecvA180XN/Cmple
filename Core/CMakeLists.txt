# Set directory paths
set(CORE_INCLUDE ${PROJECT_SOURCE_DIR}/Core/Include)
set(CORE_SOURCE ${PROJECT_SOURCE_DIR}/Core/Source)

# Define core library and runtime launcher
add_executable(${PROJECT_NAME} ${CORE_SOURCE}/main.cpp)
add_library(${PROJECT_CORE_NAME} ${CORE_SOURCE}/feature.cpp)

# Set compile requirements
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_CORE_NAME} PUBLIC cxx_std_17)

# Set include paths
target_include_directories(${PROJECT_NAME} PUBLIC ${CORE_INCLUDE})
target_include_directories(${PROJECT_CORE_NAME} PUBLIC ${CORE_INCLUDE})

# Link core and runtime launcher
target_link_libraries(${PROJECT_NAME} ${PROJECT_CORE_NAME})
