load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "glew",
    srcs = [],
    hdrs = glob(["include/GL/*.h"]),
    linkopts = ["-l/usr/lib/x86_64-linux-gnu/libGLEW.so"],
    visibility = ["//visibility:public"],
)
