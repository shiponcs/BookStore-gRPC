#include <iostream>
#include <memory>
#include <string>
#include "bookstore.grpc.pb.h"

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using bookstore::SayHello;
using bookstore::Empty;
using bookstore::HelloReply;

class BookStoreClient {
	public:
	    BookStoreClient(std::shared_ptr<Channel> channel)
	        : stub_(BookStore::NewStub(channel)) {}
	  
	    // Assembles client payload, sends it to the server, and returns its response
	    std::string sendRequest(std::string a) {
	      // Data to be sent to server
	      Empty request;
	  
	      // Container for server response
	      HelloReply reply;
	  
	      // Context can be used to send meta data to server or modify RPC behaviour
	      ClientContext context;
	  
	      // Actual Remote Procedure Call
	      Status status = stub_->sendRequest(&context, request, &reply);
	  
	      // Returns results based on RPC status
	      if (status.ok()) {
	        return reply.message();
	      } else {
	        std::cout << status.error_code() << ": " << status.error_message()
	                  << std::endl;
	        return "RPC Failed";
	      }
	    }
	  
	   private:
	    std::unique_ptr<StringReverse::Stub> stub_;
};
