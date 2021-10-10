# Define test files
add_executable(${PROJECT_TEST_NAME}
    main.cpp
    Test1.cpp
    Test2.cpp
    Test3.cpp
    Test4.cpp
    Test5.cpp
    Test6.cpp
)

# Register suite as test
add_test(NAME ${PROJECT_TEST_NAME} COMMAND ${PROJECT_TEST_NAME})

# Link with core adn testing library
target_link_libraries(${PROJECT_TEST_NAME} PUBLIC ${PROJECT_CORE_NAME} gtest)
