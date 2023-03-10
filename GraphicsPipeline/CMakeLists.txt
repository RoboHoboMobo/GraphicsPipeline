cmake_minimum_required(VERSION 3.5)

project(GraphicsPipeline LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/res/shaders)

set(STB_IMAGE_DIR vendor/stb_image)

set(HEADERS
    Renderer.h
    VertexBuffer.h
    IndexBuffer.h
    VertexArray.h
    VertexBufferLayout.h
    Shader.h
    Window.h
    ${STB_IMAGE_DIR}/stb_image.h
    Texture.h
    )

set(SOURCES
    Renderer.cpp
    VertexBuffer.cpp
    IndexBuffer.cpp
    VertexArray.cpp
    VertexBufferLayout.cpp
    Shader.cpp
    Window.cpp
    ${STB_IMAGE_DIR}/stb_image.cpp
    Texture.cpp
    )

set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/res)
set(SHADERS_DIR ${RESOURCES_DIR}/shaders)

set(SHADERS
    ${SHADERS_DIR}/fragment.shader
    ${SHADERS_DIR}/vertex.shader
    )

add_executable(GraphicsPipeline main.cpp ${HEADERS} ${SOURCES} ${SHADERS})
target_compile_features(GraphicsPipeline PRIVATE cxx_std_17)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res
    ${PROJECT_BINARY_DIR}/res)

add_dependencies(GraphicsPipeline copy_resources)

set(OPENGL_LIBRARIES ${OPENGL_LIBRARY} glfw ${GLEW_LIBRARIES})

target_link_libraries(GraphicsPipeline ${OpenCV_LIBS} ${OPENGL_LIBRARIES})
