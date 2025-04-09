#include "grpc_server.h"
#include "shm_writer.h"
#include <iostream>
#include <memory>
#include <string>
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
    std::string key = request->key();
    std::string value = request->value();

    std::cout << "Node D received -> Key: " << key << ", Value: " << value << std::endl;

    SharedMemoryWriter shm_writer("/node_d_memory", 4096);
    shm_writer.write(key + ":" + value);

    reply->set_status("RECEIVED");
    return Status::OK;
}

void RunServerD() {
    std::string server_address("0.0.0.0:50054");
    GRPCServerDImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Node D server listening on " << server_address << std::endl;

    server->Wait();
}
