cmake_minimum_required(VERSION 3.27)
# CATRENDERER
project(CR)

file(GLOB_RECURSE SOURCES "src/*.c")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(src src/glad/include src/renderer src/utils)
add_executable(CR ${SOURCES})

target_include_directories(CR PRIVATE ${CMAKE_SOURCE_DIR}/lib/cglm-0.9.4/include)
target_link_directories(CR PRIVATE ${CMAKE_SOURCE_DIR}/lib/cglm-0.9.4/lib)

target_link_libraries(CR PRIVATE ${OPENGL_LIBRARIES} glfw cglm)
