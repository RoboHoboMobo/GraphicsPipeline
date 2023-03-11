cc_library(
    name = "glfw",
    srcs = glob(["third_party/glfw/src/*.c", "third_party/glfw/src/*.h"]),
    hdrs = glob(["third_party/glfw/include/GLFW/glfw3.h"]),
    copts = ["-Ithird_party/glfw/include"],
    linkopts = ["-lglfw", "-lX11", "-lXxf86vm", "-lXrandr", "-lpthread", "-ldl"],
    visibility = ["//visibility:public"],
)
