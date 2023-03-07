cmake_minimum_required(VERSION 3.5)

project(GraphicsPipeline LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(GraphicsPipeline main.cpp)

set(OPENGL_LIBRARIES ${OPENGL_LIBRARY} glfw ${GLEW_LIBRARIES})

target_link_libraries(GraphicsPipeline ${OpenCV_LIBS} ${OPENGL_LIBRARIES})
