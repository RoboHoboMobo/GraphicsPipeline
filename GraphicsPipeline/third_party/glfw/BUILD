load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "glfw",
    srcs = glob(["third_party/glfw/src/*.c", "third_party/glfw/src/*.h"]),
    hdrs = glob(["third_party/glfw/include/GLFW/glfw3.h"]),
    copts = ["-Ithird_party/glfw/include"],
    linkopts = [
        "-l/usr/lib/x86_64-linux-gnu/libglfw.so",
        "-lX11",
        "-lXrandr",
        "-lpthread",
        "-ldl"
    ],
    visibility = ["//visibility:public"],
)
