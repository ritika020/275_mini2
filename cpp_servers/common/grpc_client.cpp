#include "grpc_client.h"
#include <iostream>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

GRPCClient::GRPCClient(const std::string& address) {
    auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
    stub_ = distributed::DataPushService::NewStub(channel);
}

bool GRPCClient::sendToNode(const std::string& key, const std::string& value) {
    distributed::DataRow row;
    row.set_key(key);
    row.set_value(value);

    distributed::Ack reply;
    ClientContext context;

    Status status = stub_->SendData(&context, row, &reply);

    if (status.ok()) {
        std::cout << "Forwarded to next node -> Key: " << key << ", Status: " << reply.status() << std::endl;
        return true;
    } else {
        std::cerr << "Failed to forward to node. Error: " << status.error_message() << std::endl;
        return false;
    }
}
