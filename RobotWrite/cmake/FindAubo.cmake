set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Aubo)

# 设置头文件路径。
set(Aubo_INCLUDE_DIRS ${INCLUDE_DIR}/libconfig/linux_x64/inc
        ${INCLUDE_DIR}/log4cplus/linux_x64/inc
        ${INCLUDE_DIR}/protobuf/linux_x64/google/protobuf
        ${INCLUDE_DIR}/robotController/Header
        ${INCLUDE_DIR}/robotSDK/inc
        )

# 设置库文件路径。
set(Aubo_LIB config log4cplus protobuf protobuf-lite protoc auborobotcontroller)
FOREACH(aubocomponent ${Aubo_LIB})
    find_library(lib_${aubocomponent} NAMES ${aubocomponent} PATHS
            ${INCLUDE_DIR}/protobuf/linux-x64/lib
            ${INCLUDE_DIR}/libconfig/linux_x64/lib
            ${INCLUDE_DIR}/log4cplus/linux_x64/lib
            ${INCLUDE_DIR}/robotController/linux_x64
            ${INCLUDE_DIR}/robotSDK/lib/linux_x64
            NO_DEFAULT_PATH)
    set(Aubo_LIBRARIES_DIRS ${Aubo_LIBRARIES_DIRS} ${lib_${aubocomponent}})
ENDFOREACH()
