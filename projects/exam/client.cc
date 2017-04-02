#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <grpc/support/log.h>
#include "example.grpc.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

class ExampleClient {
public:
	explicit ExampleClient(std::shared_ptr<Channel> channel):
		stub_(SearchService::NewStub(channel)) {}
	std::string Search(const std::string& user)
	{
		SearchRequest request;
		request.set_request(user);
		SearchResponse reply;
		ClientContext context;
		CompletionQueue cq;
		Status status;
		std::unique_ptr<ClientAsyncResponseReader<SearchResponse> > rpc(stub_->AsyncSearch(&context, request, &cq));
		rpc->Finish(&reply, &status, (void*)1);
		void* got_tag;
		bool ok = false;
		GPR_ASSERT(cq.Next(&got_tag, &ok));
		GPR_ASSERT(got_tag == (void*)1);
		GPR_ASSERT(ok);
		if(status.ok())
		{
			return reply.response();
		}else{
			return "RPC failed";
		}
	}
private:
	std::unique_ptr<SearchService::Stub> stub_;
};

int main(int argc, char** argv)
{
	ExampleClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
	std::string user("world");
	std::string reply = client.Search(user);
	std::cout << "client received: " << reply << std::endl;
	return 0;
}



























