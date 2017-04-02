#include "libevent_network.h"
#include "libevent_socket.h"
#include "../imp/common_thread.h"
#include <iostream>

class MySocket:public net::SocketEvent {
public:
	void ReadHandle(struct bufferevent *bev)
	{
		std::cout << "hello world" << std::endl;
	}
	void WriteHandle(struct bufferevent *bev){}
	void EventHandle(struct bufferevent *bev) {}		
};

class MyMain:public net::MainEvent,public CommonThread {
public:
	MyMain():net::MainEvent("127.0.0.1", 8888),CommonThread() {}

	void ListenHandle(struct bufferevent *bev)
	{
		_socket.SetBuffer(bev);
		_socket.Init();
	}
	
	void Run()
	{
		Init();
		Loop();
	}
private:
	MySocket _socket;
};

int main()
{
	MyMain mn;
	mn.Start();
	std::cout << "-2" << std::endl;
	mn.Join();
	std::cout << "-1" << std::endl;
}


