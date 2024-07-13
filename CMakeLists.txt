cmake_minimum_required(VERSION 3.27)
# CATRENDERER
project(CR)

file(GLOB_RECURSE SOURCES "src/*.c")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(src src/glad/include src/renderer src/utils)
add_executable(CR ${SOURCES})

target_link_libraries(CR PRIVATE ${OPENGL_LIBRARIES} glfw)
