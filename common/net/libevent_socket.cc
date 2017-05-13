#include "libevent_socket.h"
#include <stdlib.h>
namespace net {
	SocketEvent::SocketEvent(struct bufferevent* buffer):
		_buffer(buffer) {}
	SocketEvent::SocketEvent():
		_buffer(NULL) {}

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
}











