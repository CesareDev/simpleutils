cmake_minimum_required(VERSION 3.14)

set(TEST_SRC_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Config/TestIniLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tasks/TestScheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tasks/TestThreadPool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

add_executable(testExec ${TEST_SRC_FILE})

target_link_libraries(testExec PRIVATE ${PROJECT_NAME} Boost::unit_test_framework)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/config" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")