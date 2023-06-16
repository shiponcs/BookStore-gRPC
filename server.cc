#include <grpcpp/grpcpp.h>
#include <string>
#include <iostream>
#include <map>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "bookstore.grpc.pb.h"
#include <cstdlib>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using bookstore::BookStore;
using bookstore::Empty;
using bookstore::HellowReply;
using bookstore::Book;
using bookstore::Reply;


std::map< int, Book > db;

class BookStoreServiceImpl final : public BookStore::Service {
	Status SayHello(ServerContext* context, const Empty* request, HellowReply* reply) override {
		std::string ourReply("Hi from BookStore gRPC server");
		reply->set_message(ourReply);
		return Status::OK;
	}
	
	Status GetAllBooks(ServerContext* context, const Empty* request, ServerWriter<Book>* writer) override {
		Book book;
		book.set_id(5);
		book.set_name("GEB");
		book.set_author("ABC");
		
		writer->Write(book);
		book.set_id(33);
		writer->Write(book);
		
		return Status::OK;
	}

    Status PostBook(ServerContext* context, const Book* request, Reply* reply) override {
        std::cout << "PostBook: " << request->id() << " " << request->name() << " " << request->author() <<"\n";
        reply->set_msg("Book created with id: ");
        return  Status::OK;
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
