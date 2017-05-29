#include "libevent_socket.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
namespace net {
	SocketEvent::SocketEvent(struct bufferevent* buffer):
		_buffer(buffer)/*, _ip(std::string()), _port(0)*/ {}
	SocketEvent::SocketEvent():
		_buffer(NULL)/*, _ip(std::string()), _port(0) */{}

	SocketEvent::~SocketEvent()
	{
		bufferevent_free(_buffer);
	}

	void SocketEvent::Init()
	{
		bufferevent_setcb(_buffer,
						  SocketEvent::ReadCallBack,
						  SocketEvent::WriteCallBack,
						  SocketEvent::EventCallBack,
						  static_cast<void*>(this));
		bufferevent_enable(_buffer, EV_READ);
		bufferevent_enable(_buffer, EV_WRITE);
		//bufferevent_enable(_buffer, EV_EVENT);
	}
	
	void SocketEvent::SetBuffer(struct bufferevent *buffer)
	{
		_buffer = buffer;
	}	

	void SocketEvent::ReadCallBack(struct bufferevent *bev, void *user_data)
	{
		SocketEvent *pSocketEvent = static_cast<SocketEvent*>(user_data);
		pSocketEvent->ReadHandle(bev);
	}

	void SocketEvent::WriteCallBack(struct bufferevent *bev, void *user_data)
	{
		SocketEvent *pSocketEvent = static_cast<SocketEvent*>(user_data);
		pSocketEvent->WriteHandle(bev);
	}

	void SocketEvent::EventCallBack(struct bufferevent *bev, short events, void *user_data)
	{
		SocketEvent *pSocketEvent = static_cast<SocketEvent*>(user_data);
		pSocketEvent->EventHandle(bev);
	}

	int SocketEvent::Write(void* buffer, size_t size)
	{
		return bufferevent_write(_buffer, buffer, size);
	}

	void SocketEvent::SetSockAddr(struct sockaddr *sa, int socklen)
	{
		sockaddr_in sin;
		char ips[30];
		
		memset(ips, '\0', sizeof(ips));
		memcpy(&sin, sa, sizeof(sin));
		std::cerr << "111111" << std::endl;
		sprintf(ips, inet_ntoa(sin.sin_addr));
		std::cerr << "222222" << std::endl;
		ips[29] = '\0';
		_ip = ips;
		std::cerr << ips << std::endl;
		std::cerr << "333333" << std::endl;
		_port = sin.sin_port;
	}
	
	const std::string& SocketEvent::GetIp(void) const
	{
		return _ip;
	}
	
	int SocketEvent::GetPort() const
	{
		return _port;
	}
}











