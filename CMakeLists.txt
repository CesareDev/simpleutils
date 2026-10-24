cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(simpleutils)

set(LIB_SRC_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Config/Loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Config/IniLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Config/JsonLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Config/XmlLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Log/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tasks/Scheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tasks/ThreadPool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tasks/Time.cpp
)

add_library(${PROJECT_NAME} SHARED  ${LIB_SRC_FILE})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

add_subdirectory(test)