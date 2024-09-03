cmake_minimum_required(VERSION 3.10)
project(OceanSDKExample)

set(CMAKE_CXX_STANDARD 11)

# 指定头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 指定库文件路径
link_directories(${CMAKE_SOURCE_DIR}/lib/x64)

# 添加可执行文件
add_executable(OceanSDKExample example/example.cpp)

# 链接库文件
target_link_libraries(OceanSDKExample ocean)