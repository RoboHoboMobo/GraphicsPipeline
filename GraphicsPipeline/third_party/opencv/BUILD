cc_library(
    name = "opencv",
    hdrs = glob(["include/**/*.hpp"]),
    srcs = [],
    linkopts = ["-L$(location)/lib", "-lopencv_core", "-lopencv_highgui", "-lopencv_imgcodecs", "-lopencv_imgproc"],
    visibility = ["//visibility:public"],
)
