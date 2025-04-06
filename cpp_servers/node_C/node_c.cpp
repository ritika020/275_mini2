#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"
#include "../common/shared_memory.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class DataServiceImpl : public DataService::Service {
    Status PushData(ServerContext* context, const DataPacket* request, Ack* reply) override {
        std::string payload = request->payload();
        std::cout << "[Node C] Received: " << payload << std::endl;
        write_to_shared_memory("/node_c", payload);
        reply->set_received(true);
        return Status::OK;
    }
};

int main() {
    std::string addr("0.0.0.0:50052");
    DataServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "[Node C] Listening on " << addr << std::endl;
    server->Wait();
}
