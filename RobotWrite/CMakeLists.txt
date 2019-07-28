cmake_minimum_required(VERSION 3.14)
project(Test)

set(CMAKE_CXX_STANDARD 14)

set(CAKE_CXX_FLAGS  " g3 -Wall" )


# 设置example的路径
set(EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)

# 设置以来的路径
set(DEPENDENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependents)

# include 路径
set(PROJECT_INCLUDE_DIRS
        ${DEPENDENTS_DIR}/libconfig/linux_x64/inc;
        ${DEPENDENTS_DIR}/log4cplus/linux_x64/inc;
        ${DEPENDENTS_DIR}/protobuf/linux_x64/google/protobuf/inc;
        ${DEPENDENTS_DIR}/robotController/Header;
        ${DEPENDENTS_DIR}/robotSDK/inc;
        ${EXAMPLE_DIR}1
        )

include_directories(${PROJECT_INCLUDE_DIRS})


# 设置查找的库组件
SET(PROJECT_LIB_COMPONENTS config;log4cplus;protobuf;protobuf-lite;protoc;auborobotcontroller)

FOREACH(aubocomponent ${PROJECT_LIB_COMPONENTS})
    find_library(lib_${aubocomponent} NAMES ${aubocomponent} PATHS
            ${DEPENDENTS_DIR}/protobuf/linux-x64/lib
            ${DEPENDENTS_DIR}/libconfig/linux_x64/lib
            ${DEPENDENTS_DIR}/log4cplus/linux_x64/lib
            ${DEPENDENTS_DIR}/robotController/linux_x64
            ${DEPENDENTS_DIR}/robotSDK/lib/linux_x64
            ${EXAMPLE_DIR}
            NO_DEFAULT_PATH)
    set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES};${lib_${aubocomponent}})
ENDFOREACH()

message(status "========================${PROJECT_LIBRARIES}")


# 指定example文件夹的源码位置
aux_source_directory(example DIR_SRCS)



SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/bin" CACHE PATH "Runtime directory" FORCE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs" CACHE PATH "Library directory" FORCE)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs" CACHE PATH "Archive directory" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/dependents/qt)

file(
        WRITE
        ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/qt.conf
        "[Paths]
Plugins=${CMAKE_CURRENT_SOURCE_DIR}/dependents/qt/plugins"
)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

SET(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})

include_directories("/usr/include/eigen3")

# 头文件和链接库的路径
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} )



# 引入opencv相关以来
set(PREBUILT_DIR ${CMAKE_SOURCE_DIR}/dependents)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
message(STATUS "test:${CMAKE_MODULE_PATH}")
find_package(OpenCV REQUIRED)

# 加载pytorch相关依赖
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CBTC_PREBUILT_DIR}/libtorch_cpu")
find_package(Torch REQUIRED)
include_directories(${TORCH_INCLUDE_DIRS})

include_directories("/usr/include/eigen3")

find_package(PCL REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


# 引入kenect2相关的依赖
set(FREENECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/denpendents/include)
set(FREENECT_LIBRARIES ${PROJECT_SOURCE_DIR}/denpendents/lib)

include_directories(${FREENECT_INCLUDE_DIRS})
link_directories(${FREENECT_LIBRARIES})



add_executable(test src/main.cpp #[[src/20_KenectDemo_SAVE.cpp]] src/MainWindow.cpp src/Kinect.cpp)
target_link_libraries(test libfreenect2.so ${OpenCV_LIBRARIES}  ${QT_LIBRARIES} ${PROJECT_LIBRARIES} ${TORCH_LIBRARIES})


add_subdirectory(src)