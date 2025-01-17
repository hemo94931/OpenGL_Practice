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

project (TankWar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
# 	file(COPY "${PROJECT_SOURCE_DIR}/resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# endif (NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_PAR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RESOURCE_PAR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_PAR_PATH}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${SOURCE_PAR_PATH}/*.h")
file(GLOB_RECURSE SHADER_FILES "${SOURCE_PAR_PATH}/*.vs" "${SOURCE_PAR_PATH}/*.fs" )

set(PROJECT_SOURCES
    ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES}
)

foreach(_source IN ITEMS ${HEADER_FILES})
    get_filename_component(_source_path "${_source}" PATH)

    if(_source_path STREQUAL "${SOURCE_PAR_PATH}")
        set(_group_path "Uncategorized Files")
    else()
        file(RELATIVE_PATH _source_path_rel "${SOURCE_PAR_PATH}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    endif()

    source_group("${_group_path}/Header" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)

    if(_source_path STREQUAL "${SOURCE_PAR_PATH}")
        set(_group_path "Uncategorized Files")
    else()
        file(RELATIVE_PATH _source_path_rel "${SOURCE_PAR_PATH}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    endif()

    source_group("${_group_path}/Source" FILES "${_source}")
endforeach()

source_group("Shader Files" FILES ${SHADER_FILES})

# 文件不同时不会重新复制
# file(COPY "${PROJECT_SOURCE_DIR}/resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# 文件不同时可重新复制
execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

set(SHADER_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources/shaders")
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_BINARY_DIR}"
)

foreach(SHADER ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    add_custom_command(
        TARGET copy_shaders POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER}
        "${SHADER_BINARY_DIR}/${SHADER_NAME}"
        DEPENDS ${SHADER}
    )
endforeach()

set(GLAD_FILE glad.c)
add_library(GLAD ${GLAD_FILE})
target_include_directories(GLAD PUBLIC ${PROJECT_SOURCE_DIR}/../includes)

file(GLOB SUBDIRS RELATIVE ${SOURCE_PAR_PATH} ${SOURCE_PAR_PATH}/*)

foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${SOURCE_PAR_PATH}/${subdir})
        include_directories(${SOURCE_PAR_PATH}/${subdir})
    endif()
endforeach()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libs)
target_link_libraries(${PROJECT_NAME} PRIVATE GLAD assimp-vc143-mtd.lib glfw3.lib opengl32.lib)