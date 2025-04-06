#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"
#include "../common/shared_memory.hpp"
#include "../common/config.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace std;

class DataServiceImpl : public DataService::Service {
    Status PushData(ServerContext* context, const DataPacket* request, Ack* reply) override {
        std::string payload = request->payload();
        std::cout << "[Node B] Received: " << payload << std::endl;
        write_to_shared_memory("/node_b", payload);
        reply->set_received(true);

        // Forward to child C
        auto children = get_children("B");
        for (const auto& child : children) {
            auto stub = DataService::NewStub(grpc::CreateChannel("localhost:50052", grpc::InsecureChannelCredentials()));
            DataPacket pkt;
            pkt.set_id(request->id());
            pkt.set_payload("[FWD B→C] " + payload);
            Ack ack;
            grpc::ClientContext ctx;
            stub->PushData(&ctx, pkt, &ack);
        }

        return Status::OK;
    }
};

int main() {
    std::string addr("0.0.0.0:50051");
    DataServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "[Node B] Listening on " << addr << std::endl;
    server->Wait();
}
