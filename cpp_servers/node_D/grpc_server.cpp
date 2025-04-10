#include "grpc_server.h"
#include "shm_writer.h"
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <sys/resource.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

Status GRPCServerDImpl::SendData(ServerContext* context,
                                 const distributed::DataRow* request,
                                 distributed::Ack* reply) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string key = request->key();
    std::string value = request->value();

    std::cout << "Node D received -> Key: " << key << ", Value: " << value << std::endl;

    SharedMemoryWriter shm_writer("/node_d_memory", 4096);
    shm_writer.write(key + ":" + value);

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    std::cout << "Node D memory: " << usage.ru_maxrss / 1024.0 << " MB" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Node D handled row in " << ms << " ms" << std::endl;

    reply->set_status("RECEIVED");
    return Status::OK;
}
