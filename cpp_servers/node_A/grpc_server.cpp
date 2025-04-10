#include "grpc_server.h"
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include "partition.h"
#include "grpc_client.h"
#include "shm_writer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Called whenever a DataRow is received
// Status GRPCServerImpl::SendData(ServerContext* context,
//                                 const distributed::DataRow* request,
//                                 distributed::Ack* reply) {
//     std::string key = request->key();
//     std::string value = request->value();

//     std::cout << "Node A received -> Key: " << key << ", Value: " << value << std::endl;

//     // Perform global partition to decide next node
//     int node = Partitioner::global_partition(key);
//     std::string target_address = (node == 0) ? "localhost:50052" : "localhost:50053"; // Node B or C

//     GRPCClient forwarder(target_address);
//     forwarder.sendToNode(key, value);

//     SharedMemoryWriter shm_writer("/node_a_memory", 4096);
//     shm_writer.write(key + ":" + value);

//     reply->set_status("RECEIVED");
//     return Status::OK;
// }

grpc::Status GRPCServerImpl::SendData(grpc::ServerContext* context,
                                      const distributed::DataRow* request,
                                      distributed::Ack* reply) {
    std::cout << "🟢 REACHED SendData handler: " << request->key() << std::endl;
    reply->set_status("RECEIVED");
    return grpc::Status::OK;
}



void RunServerA() {
    std::string server_address("0.0.0.0:50051");
    GRPCServerImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Node A server listening on " << server_address << std::endl;

    server->Wait();
}
