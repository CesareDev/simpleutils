cmake_minimum_required(VERSION 3.14)

project(test_simpleutils)

set(TEST_SRC_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/config" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(${PROJECT_NAME} ${TEST_SRC_FILE})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC simpleutils)