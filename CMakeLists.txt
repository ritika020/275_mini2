# # Top-level CMakeLists.txt
# cmake_minimum_required(VERSION 3.10)
# project(mini2)

# set(CMAKE_CXX_STANDARD 17)

# # Prevent conflict with incomplete protobuf targets
# set(protobuf_MODULE_COMPATIBLE TRUE)

# find_package(Protobuf REQUIRED)
# find_package(gRPC REQUIRED)

# add_subdirectory(cpp_servers/common)
# add_subdirectory(cpp_servers/node_b)
# add_subdirectory(cpp_servers/node_c)

# target_include_directories(common PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     /opt/homebrew/include
# )


cmake_minimum_required(VERSION 3.14)
project(mini2_distributed_system)

set(CMAKE_CXX_STANDARD 17)

# Proto output locations
set(PROTO_SRCS
    ${CMAKE_SOURCE_DIR}/proto/data.pb.cc
    ${CMAKE_SOURCE_DIR}/proto/data.grpc.pb.cc
)

set(PROTO_HDRS
    ${CMAKE_SOURCE_DIR}/proto/data.pb.h
    ${CMAKE_SOURCE_DIR}/proto/data.grpc.pb.h
)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/cpp_servers/common)
include_directories(SYSTEM "/opt/homebrew/include")
link_directories("/opt/homebrew/lib")

find_package(Protobuf REQUIRED CONFIG)
find_package(gRPC REQUIRED CONFIG)

# Helper macro
function(add_node name path)
    add_executable(${name}
        ${path}/main.cpp
        ${path}/grpc_server.cpp
        ${CMAKE_SOURCE_DIR}/cpp_servers/common/grpc_client.cpp
        ${CMAKE_SOURCE_DIR}/cpp_servers/common/partition.cpp
        ${CMAKE_SOURCE_DIR}/cpp_servers/common/shm_writer.cpp

        ${PROTO_SRCS}
    )

    target_include_directories(${name} PRIVATE 
    ${CMAKE_SOURCE_DIR}/proto
    ${CMAKE_SOURCE_DIR}/cpp_servers/common)

    target_link_libraries(${name}
        gRPC::grpc++
        protobuf::libprotobuf
        absl::strings
        absl::synchronization
        pthread
    )
endfunction()

# Add each node (case-sensitive)
add_node(node_A ${CMAKE_SOURCE_DIR}/cpp_servers/node_A)
add_node(node_B ${CMAKE_SOURCE_DIR}/cpp_servers/node_B)
add_node(node_C ${CMAKE_SOURCE_DIR}/cpp_servers/node_C)
add_node(node_D ${CMAKE_SOURCE_DIR}/cpp_servers/node_D)
add_node(node_E ${CMAKE_SOURCE_DIR}/cpp_servers/node_E)


# cmake_minimum_required(VERSION 3.14)
# project(mini2_distributed_system)

# set(CMAKE_CXX_STANDARD 17)

# # Proto output locations (manually generated)
# set(PROTO_SRCS
#     ${CMAKE_SOURCE_DIR}/proto/data.pb.cc
#     ${CMAKE_SOURCE_DIR}/proto/data.grpc.pb.cc
# )

# set(PROTO_HDRS
#     ${CMAKE_SOURCE_DIR}/proto/data.pb.h
#     ${CMAKE_SOURCE_DIR}/proto/data.grpc.pb.h
# )
# find_package(gRPC REQUIRED CONFIG)
# find_package(Protobuf REQUIRED CONFIG)

# include_directories(${CMAKE_SOURCE_DIR}/proto)

# # Add system include directory for Homebrew's protobuf headers
# include_directories(SYSTEM "/opt/homebrew/include")

# # Add library path
# link_directories("/opt/homebrew/lib")

# # Helper macro to build a node
# function(add_node name path)
#     file(GLOB SOURCES ${path}/*.cpp ${path}/*.h)
#     # add_executable(${name} ${SOURCES} ${PROTO_SRCS})
# #     add_executable(node_A
# #     ${CMAKE_SOURCE_DIR}/node_A/main.cpp
# #     ${CMAKE_SOURCE_DIR}/node_A/grpc_server.cpp
# #     ${PROTO_SRCS}
# # )

#     target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/proto)
#     target_link_libraries(${name}
#         gRPC::grpc++
#         protobuf::libprotobuf
#         absl::strings
#         absl::synchronization
#         pthread
#     )
# endfunction()

# add_node(node_A ${CMAKE_SOURCE_DIR}/node_A)
# add_node(node_B ${CMAKE_SOURCE_DIR}/node_B)
# add_node(node_C ${CMAKE_SOURCE_DIR}/node_C)
# add_node(node_D ${CMAKE_SOURCE_DIR}/node_D)
# add_node(node_E ${CMAKE_SOURCE_DIR}/node_E)