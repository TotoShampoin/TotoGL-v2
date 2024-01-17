cmake_minimum_required(VERSION 3.5)
set(BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TotoGL)

set(TOTOGL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TOTOGL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE TOTOGL_INCLUDE_FILES CONFIGURE_DEPENDS ${TOTOGL_INCLUDE_DIR}/*.hpp ${TOTOGL_INCLUDE_DIR}/*.tpp)
file(GLOB_RECURSE TOTOGL_SOURCE_FILES CONFIGURE_DEPENDS ${TOTOGL_SOURCE_DIR}/*.cpp)


add_library(totogl INTERFACE)
target_sources(totogl INTERFACE ${TOTOGL_SOURCE_FILES} ${TOTOGL_INCLUDE_FILES})
target_compile_features(totogl INTERFACE cxx_std_23)

target_include_directories(totogl INTERFACE ${OPENGL_INCLUDE_DIR})
target_include_directories(totogl INTERFACE ${GLEW_INCLUDE_DIR})
target_link_libraries(totogl INTERFACE OpenGL glfw GLU GLEW glm)

target_include_directories(totogl INTERFACE ${TOTOGL_SOURCE_DIR})
target_include_directories(totogl INTERFACE ${TOTOGL_INCLUDE_DIR})

if (MSVC)
    target_compile_options(totogl INTERFACE /W3)
else()
    target_compile_options(totogl INTERFACE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()
