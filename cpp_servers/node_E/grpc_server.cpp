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

Status GRPCServerEImpl::SendData(ServerContext* context,
                                 const distributed::DataRow* request,
                                 distributed::Ack* reply) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string key = request->key();
    std::string value = request->value();

    std::cout << "Node E received -> Key: " << key << ", Value: " << value << std::endl;

    SharedMemoryWriter shm_writer("/node_e_memory", 4096);
    shm_writer.write(key + ":" + value);

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    std::cout << "Node E memory usage: " << usage.ru_maxrss / 1024.0 << " MB" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Node E handled row in " << duration << " ms\n";

    reply->set_status("RECEIVED");
    return Status::OK;
}

void RunServerE() {
    std::string server_address("0.0.0.0:50055");
    GRPCServerEImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Node E server listening on " << server_address << std::endl;

    server->Wait();
}
