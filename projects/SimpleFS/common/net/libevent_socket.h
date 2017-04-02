#ifndef _LIBEVENT_SOCKET_H_
#define _LIBEVENT_SOCKET_H_
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>

namespace net{

	class SocketEvent{
	public:
		SocketEvent();
		virtual ~SocketEvent();
		void SetBuffer(struct bufferevent *buffer);
		void Init();
	private:
		static void ReadCallBack(struct bufferevent *bev, void *user_data);
		static void WriteCallBack(struct bufferevent *bev, void *user_data);		
		static void EventCallBack(struct bufferevent *bev, short events, void *user_data);
	public:
		virtual void ReadHandle(struct bufferevent *bev) = 0;
		virtual void WriteHandle(struct bufferevent *bev) = 0;
		virtual void EventHandle(struct bufferevent *bev)= 0;  
	private:
		struct bufferevent *_buffer;
	};
}

#endif /* _LIBEVENT_SOCKET_H_ */
