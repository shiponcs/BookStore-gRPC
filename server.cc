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
using grpc::StatusCode;

using bookstore::BookStore;
using bookstore::Empty;
using bookstore::HellowReply;
using bookstore::Book;
using bookstore::Reply;
using bookstore::SearchRequest;


std::map< int, Book > db;

class BookStoreServiceImpl final : public BookStore::Service {
	Status SayHello(ServerContext* context, const Empty* request, HellowReply* reply) override {
		std::string ourReply("Hi from BookStore gRPC server");
		reply->set_message(ourReply);
		return Status::OK;
	}
	
	Status GetAllBooks(ServerContext* context, const Empty* request, ServerWriter<Book>* writer) override {
		Book book;

        for(auto const& entry: db) {
            book.set_id(entry.second.id());
            book.set_name(entry.second.name());
            book.set_author(entry.second.author());
            writer->Write(book);
        }

		return Status::OK;
	}

    Status GetABookById(ServerContext* context, const SearchRequest* request, Book* reply) override {
        int requestedId = request->id();
        if(db.find(requestedId) == db.end()) {
            return Status(StatusCode::NOT_FOUND, "No book entry found for this id");

        }
        Book requestedBook = db[requestedId];
        reply->CopyFrom(requestedBook);
        return Status::OK;
    }

    Status DeleteABook(ServerContext* context, const SearchRequest* request, Empty* reply) override {
        int requestedId = request->id();
        if(db.find(requestedId) == db.end()) {
            return Status(StatusCode::NOT_FOUND, "No book entry found for this id");
        }
        db.erase(requestedId);
        return Status::OK;
    }

    Status PostBook(ServerContext* context, const Book* request, Reply* reply) override {
        srand((unsigned) time((NULL)));
        int id = rand();
        Book book;
        book.set_id(id);
        book.set_name(request->name());
        book.set_author(request->author());
        db[id] = book;
        reply->set_msg("Book created with id: " + std::to_string(id));
        return  Status::OK;
    }

    Status UpdateABook(ServerContext* context, const Book* request, Book* reply) override {
        int requestedId = request->id();
        if(db.find(requestedId) == db.end()) {
            return Status(StatusCode::NOT_FOUND, "No book entry found for this id");
        }
        db[requestedId] = *request;

        reply->CopyFrom(*request);

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
