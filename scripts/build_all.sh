#!/bin/bash
set -e
echo "Generating gRPC files..."
protoc -Igrpc_definitions \
  --cpp_out=cpp_servers/common \
  --grpc_out=cpp_servers/common \
  --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
  grpc_definitions/data.proto

python3 -m grpc_tools.protoc \
  -Igrpc_definitions \
  --python_out=python_clients \
  --grpc_python_out=python_clients \
  grpc_definitions/data.proto

mkdir -p build && cd build
cmake ..
make -j4
echo "Build complete."
