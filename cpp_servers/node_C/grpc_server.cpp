#include "grpc_server.h"
#include "partition.h"
#include "shm_writer.h"
#include "grpc_client.h"

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

Status GRPCServerCImpl::SendData(ServerContext* context,
                                 const distributed::DataRow* request,
                                 distributed::Ack* reply) {
    std::string key = request->key();
    std::string value = request->value();

    std::cout << "Node C received -> Key: " << key << ", Value: " << value << std::endl;

    // Perform local partition to decide next node
    int node = std::hash<std::string>{}(key) % 3;
    if (node == 0) {
        SharedMemoryWriter shm_writer("/node_c_memory", 4096);
        shm_writer.write(key + ":" + value);
    } else {
        std::string target_address = (node == 1) ? "localhost:50054" : "localhost:50055"; // Node D or E
        GRPCClient forwarder(target_address);
        forwarder.sendToNode(key, value);
    }

    reply->set_status("RECEIVED");
    return Status::OK;
}

void RunServerC() {
    std::string server_address("0.0.0.0:50053");
    GRPCServerCImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Node C server listening on " << server_address << std::endl;

    server->Wait();
}
