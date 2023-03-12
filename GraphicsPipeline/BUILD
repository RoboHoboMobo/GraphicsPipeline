load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "GraphicsPipeline",
    includes = ["include"],
    srcs = [
        "src/main.cpp",
        "src/IndexBuffer.cpp",
        "src/Shader.cpp",
        "src/VertexBuffer.cpp",
        "src/Texture.cpp",
        "src/VertexBufferLayout.cpp",
        "src/Renderer.cpp",
        "src/VertexArray.cpp",
        "src/Window.cpp",
        "include/IndexBuffer.h",
        "include/Shader.h",
        "include/VertexBuffer.h",
        "include/Texture.h",
        "include/VertexBufferLayout.h",
        "include/Renderer.h",
        "include/VertexArray.h",
        "include/Window.h"
    ],
    deps = [
        "//third_party/glew:glew",
        "//third_party/glfw:glfw",
        "//third_party/opencv:opencv",
        "//third_party/stb_image:stb_image"
    ],
    data = [
        "res/shaders/fragment.shader",
        "res/shaders/vertex.shader",
        "res/textures/pikachu.png"
    ],
    linkopts = ["-lGL", "-lGLU"],
)

