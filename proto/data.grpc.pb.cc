// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: data.proto

#include "data.pb.h"
#include "data.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace distributed {

static const char* DataPushService_method_names[] = {
  "/distributed.DataPushService/SendData",
};

std::unique_ptr< DataPushService::Stub> DataPushService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DataPushService::Stub> stub(new DataPushService::Stub(channel, options));
  return stub;
}

DataPushService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SendData_(DataPushService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DataPushService::Stub::SendData(::grpc::ClientContext* context, const ::distributed::DataRow& request, ::distributed::Ack* response) {
  return ::grpc::internal::BlockingUnaryCall< ::distributed::DataRow, ::distributed::Ack, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendData_, context, request, response);
}

void DataPushService::Stub::async::SendData(::grpc::ClientContext* context, const ::distributed::DataRow* request, ::distributed::Ack* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::distributed::DataRow, ::distributed::Ack, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendData_, context, request, response, std::move(f));
}

void DataPushService::Stub::async::SendData(::grpc::ClientContext* context, const ::distributed::DataRow* request, ::distributed::Ack* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::distributed::Ack>* DataPushService::Stub::PrepareAsyncSendDataRaw(::grpc::ClientContext* context, const ::distributed::DataRow& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::distributed::Ack, ::distributed::DataRow, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendData_, context, request);
}

::grpc::ClientAsyncResponseReader< ::distributed::Ack>* DataPushService::Stub::AsyncSendDataRaw(::grpc::ClientContext* context, const ::distributed::DataRow& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendDataRaw(context, request, cq);
  result->StartCall();
  return result;
}

DataPushService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataPushService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataPushService::Service, ::distributed::DataRow, ::distributed::Ack, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataPushService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::distributed::DataRow* req,
             ::distributed::Ack* resp) {
               return service->SendData(ctx, req, resp);
             }, this)));
}

DataPushService::Service::~Service() {
}

::grpc::Status DataPushService::Service::SendData(::grpc::ServerContext* context, const ::distributed::DataRow* request, ::distributed::Ack* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace distributed

