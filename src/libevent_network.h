#ifndef __LIBEVENT_NETWORK_H__
#define __LIBEVENT_NETWORK_H__
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
namespace net{

	class MainEvent
	{
	public:
		MainEvent(const std::string& address, int port);
		virtual ~MainEvent();
		void Init();
		void Loop();
		struct event_base* getBase();
	private:
		static void ListenCallBack(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *use_data);
		static void SignalCallBack(evutil_socket_t sig, short events, void *user_data);
	public:
		virtual void ListenHandle(struct bufferevent *bev) = 0;
	protected:
		struct evconnlistener *_listener;
		std::string _address;
		int _port;
		struct event_base *_base;
	public:
		static struct event_base *gEventBase;
		static void InstanceEventBase();
	};

}
#endif /* __LIBEVENT_NETWORK_H_ */

