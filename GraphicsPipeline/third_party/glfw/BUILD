load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "glfw",
    srcs = glob([
        "third_party/glfw/src/*.c",
        "third_party/glfw/src/*.h",
        "libglfw3.a"
    ]),
    hdrs = ["include/GLFW/glfw3.h"],
    linkopts = [
        "-lX11",
        "-lpthread",
        "-ldl"
    ],
    visibility = ["//visibility:public"],
)
