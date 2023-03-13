load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "glew",
    srcs = ["libGLEW.a"],
    hdrs = glob(["include/GL/*.h"]),
    visibility = ["//visibility:public"],
)
