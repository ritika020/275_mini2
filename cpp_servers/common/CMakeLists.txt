add_library(common
    shared_memory.cpp
    config.cpp
    data.pb.cc
    data.grpc.pb.cc
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

target_link_libraries(common
  PUBLIC
    gRPC::grpc++
    protobuf::libprotobuf
)
