# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(mini2)

set(CMAKE_CXX_STANDARD 17)

# Prevent conflict with incomplete protobuf targets
set(protobuf_MODULE_COMPATIBLE TRUE)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_subdirectory(cpp_servers/common)
add_subdirectory(cpp_servers/node_b)
add_subdirectory(cpp_servers/node_c)
