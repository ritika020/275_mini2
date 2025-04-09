#pragma once

#include <grpcpp/grpcpp.h>
#include "proto/data.grpc.pb.h"

class GRPCServerEImpl final : public distributed::DataPushService::Service {
public:
    grpc::Status SendData(grpc::ServerContext* context,
                          const distributed::DataRow* request,
                          distributed::Ack* reply) override;
};

void RunServerE();
