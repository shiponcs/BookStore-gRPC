#include <grpcpp/grpcpp.h>
#include <string>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "bookstore.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using bookstore::BookStore;
using bookstore::Empty;
using bookstore::HellowReply;

class BookStoreServiceImpl final : public BookStore::Service {
	Status SayHello(ServerContext* context, const Empty* request, HellowReply* reply) override {
		std::string ourReply("Hi from BookStore gRPC server");
		reply->set_message(ourReply);
		return Status::OK;
	}
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  BookStoreServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();


  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which
  // communication with client takes place
  builder.RegisterService(&service);

  // Assembling the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on port: " << server_address << std::endl;

  server->Wait();
}


int main(int argc, char** argv) {
  RunServer();
  return 0;
}
