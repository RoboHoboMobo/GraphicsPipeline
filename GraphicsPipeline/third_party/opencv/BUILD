cc_library(
    name = "opencv",
    hdrs = glob(["include/**/*.h*"]),
    includes = ["include"],
    linkopts = [
        "-L/usr/local/lib",
        "-l:libopencv_core.so",
        "-l:libopencv_highgui.so",
        "-l:libopencv_videoio.so",
    ],
    visibility = ["//visibility:public"],
)
