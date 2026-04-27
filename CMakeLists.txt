cmake_minimum_required(VERSION 3.22)
project(RADAR-H)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)

# 收集所有 src 下的 cpp 文件作为可执行的源
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/config/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cxx
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# 包含目录（Eigen 用系统包含路径或指定路径）
set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/config
    /usr/include/eigen3
)
set(THIRTY_PARTY_LIBS
    yaml-cpp
    ${OpenCV_LIBS}
)
add_executable(RADAR-H ${SRC_LIST})

target_include_directories(RADAR-H PRIVATE ${INCLUDE_DIRS})
target_link_libraries(RADAR-H PRIVATE ${THIRTY_PARTY_LIBS})
