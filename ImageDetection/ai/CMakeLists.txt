cmake_minimum_required(VERSION 3.1)

project (libtorch_mnist CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(OpenCV REQUIRED)

# 引入头文件目录
include_directories("/opt/cobotsys/3rdparty/libtorch_cpu/include")

# 查找库文件
find_library(torch_libs NAMES caffe2 gloo HINTS /opt/cobotsys/3rdparty/libtorch_cpu/lib)

message(STATUS "888=889=====================================${torch_libs8}")

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(imageDetection)