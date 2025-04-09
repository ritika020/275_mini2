#pragma once

#include <string>
#include "proto/data.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class GRPCClient {
public:
    GRPCClient(const std::string& address);
    bool sendToNode(const std::string& key, const std::string& value);

private:
    std::unique_ptr<distributed::DataPushService::Stub> stub_;
};