cmake_minimum_REQUIRED(VERSION 3.22)

project (Test_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLAD_FILE src/glad.c)
set(SOURCE_FILE src/main.cpp)

add_library(GLAD ${GLAD_FILE})
target_include_directories(GLAD PUBLIC ${PROJECT_SOURCE_DIR}/../includes)

add_executable(${PROJECT_NAME} ${SOURCE_FILE})
target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libs)
target_link_libraries(${PROJECT_NAME} PRIVATE GLAD glfw3.lib opengl32.lib)