cmake_minimum_REQUIRED(VERSION 3.22)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  #在命令行中输出message里的信息
  message("Setting build type to 'Debug' as none was specified.")
  #不管CACHE里有没有设置过CMAKE_BUILD_TYPE这个变量，Debug
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

  # 当使用cmake-gui的时候，设置构建级别的四个可选项
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

project (OpenGLTest_9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY "${PROJECT_SOURCE_DIR}/resource" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

set(GLAD_FILE glad.c)
add_library(GLAD ${GLAD_FILE})
target_include_directories(GLAD PUBLIC ${PROJECT_SOURCE_DIR}/../includes)

FILE (GLOB SOURCE_FILES src/*)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libs)
target_link_libraries(${PROJECT_NAME} PRIVATE GLAD glfw3.lib opengl32.lib)