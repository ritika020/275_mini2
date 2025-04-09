#pragma once

#include <grpcpp/grpcpp.h>
#include "proto/data.grpc.pb.h"

class GRPCServerImpl final : public distributed::DataPushService::Service {
public:
    // Override SendData from proto definition
    grpc::Status SendData(grpc::ServerContext* context,
                          const distributed::DataRow* request,
                          distributed::Ack* reply) override;
};

void RunServerA();