add_library(common
    shared_memory.cpp
    config.cpp
    data.pb.cc
    data.grpc.pb.cc
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(common PUBLIC grpc++ protobuf)
