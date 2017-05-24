#include "libevent_network.h"
#include "libevent_socket.h"
#include "package_analysis.h"
#include "../imp/common_thread.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "test_message.h"

#include <future>
#include <thread>
#include <queue>
std::queue<std::promise<int>* > queue;
//std::promise<int> promis;
using namespace net;
class MySocket:public SocketEvent, public PackageAnalysis {
public:
//	MySocket(struct bufferevent *bev) : net::SocketEvent(bev) {}
	MySocket():PackageAnalysis(MySocket::HandleNetPack) {};
	void ReadHandle(struct bufferevent *bev);
	void WriteHandle(struct bufferevent *bev){}
	void EventHandle(struct bufferevent *bev) {}
private:
	static void HandleNetPack(void* header);
};


void MySocket::ReadHandle(struct bufferevent* bev)
{
	std::cout << "ReadHandle" << std::endl;
	struct evbuffer *input =bufferevent_get_input(bev);
    size_t sz=evbuffer_get_length(input);  
    if (sz> 0)
    {   
        char* buffer = new char[sz];
        memset(buffer, 0, sz);
        bufferevent_read(bev,buffer,sz);
		std::cout << "sz = " << sz << std::endl;
        TcpDataSplit(buffer, sz);
        delete buffer;
    } 
}

void MySocket::HandleNetPack(void* header)
{
	NetDataHeader* head = static_cast<NetDataHeader*>(header);
	if(head->data_type_ == 1)
	{
		std::cout <<"data_type: " << head->data_type_ << std::endl;
		Message* msg = static_cast<Message*>(header);
		std::cout << msg->a << std::endl;
		std::cout << msg->s << std::endl;
		//	promis.set_value(1001);
		std::promise<int>* promis = queue.front();
		queue.pop();
		promis->set_value(1002);
	}
}

class MyMain:public MainEvent,public CommonThread {
public:
	MyMain():MainEvent("127.0.0.1", 8888),CommonThread() {}

	void ListenHandle(struct bufferevent *bev)
	{
		_socket.SetBuffer(bev);
		_socket.Init();
	}
	
	void Run()
	{
//		Init();
		Loop();
	}
	void SendMessage(void* event, void* data);
	MySocket* Connection(const std::string& ip, int32_t port);
private:
	MySocket _socket;
	MySocket* MyLink;
};

MySocket* MyMain::Connection(const std::string& ip, int32_t port)
{
	evutil_socket_t sockfd;
	int status, save_errno;
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	status = inet_aton(ip.c_str(), &server_addr.sin_addr);
	if(!status)
	{
//		LogError("DataServer::Connection status == 0");
		std::cout << "k1--------------------" << std::endl;
		return nullptr;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
//		LogError("DataServer::Connection -1 == sockfd");
		std::cout << "k2--------------------" << std::endl;
		return nullptr;
	}
	status = connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr));
	if(-1 == status)
	{
//		LogError("DataServer::Connection -1 == sockfd");
		std::cout << "k3------------------" << std::endl;
		return nullptr;
	}
	
/*	struct bufferevent* bev = bufferevent_socket_new(_base, sockfd, BEV_OPT_CLOSE_ON_FREE);
	struct event* ev_cmd = event_new(_base, STDIN_FILENO,  
                                      EV_READ | EV_PERSIST, cmd_msg_cb,  
                                      static_cast<void*>(bev));
	event_add(ev_cmd, NULL);
*/
	struct bufferevent* bev = bufferevent_socket_new(getBase(), sockfd, BEV_OPT_CLOSE_ON_FREE);
	MySocket* data_event = new MySocket();
	if(nullptr == data_event)
	{
//		LogError("DataServer::Connection nullptr == data_event");
		std::cout << "k4----------------------" << std::endl;
		return nullptr;
	}
	std::cout << "k5----------------------" << std::endl;
	data_event->SetBuffer(bev);
	data_event->Init();
	return data_event;
}

int main()
{
	MyMain mn;
	mn.Init();
	MySocket* my_socket = mn.Connection("127.0.0.1", 8889);
	std::promise<int> promis;
	std::future<int> result = promis.get_future();
	queue.push(&promis);
//	char  buffer[] = "hello world";
	mn.Start();
	std::cout << "-2" << std::endl;
//	my_socket->Write(static_cast<void*>(buffer), 12);
	std::cout << "fff:" << result.get() << std::endl;
	mn.Join();
	std::cout << "-1" << std::endl;
}


