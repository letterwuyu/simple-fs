#include "libevent_network.h"
#include <event2/event.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <functional>
#include <iostream>

namespace net {
	
	MainEvent::MainEvent(const std::string& address, int port):
		_address(address), _port(port), _base(NULL) {}

	MainEvent::~MainEvent() {}

	void MainEvent::Init()
	{
		struct sockaddr_in sin;

		MainEvent::InstanceEventBase();
		_base = gEventBase;

		if(!_base) {
			std::cerr << "could not initialize libevent!" << std::endl;
		}

		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(_address.c_str());
		sin.sin_port = htons(_port);

		_listener = evconnlistener_new_bind(_base, 
			ListenCallBack,
			static_cast<void*>(this),
			LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
			-1,
			reinterpret_cast<struct sockaddr*>(&sin),
			sizeof(sin)
			);
		if(!_listener) {
			std::cerr << "Could not create a listener!" << std::endl;
		}
		struct event *signal_event;
		signal_event = evsignal_new(_base, SIGINT, MainEvent::SignalCallBack, static_cast<void*>(_base));
		if(!signal_event || event_add(signal_event, NULL) < 0) {
			std::cerr << "Could not create add a signal event!" << std::endl;
		}
		event_free(signal_event);
	}

	void MainEvent::Loop() {
		event_base_dispatch(_base);
	}

	struct event_base* MainEvent::getBase() {
		return _base;		
	}

	void MainEvent::SignalCallBack(evutil_socket_t sig, short events, void *user_data) {
		struct event_base *base = static_cast<struct event_base*>(user_data);
		struct timeval delay = {2, 0};
		event_base_loopexit(base, &delay);
	}

	void MainEvent::ListenCallBack(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data) {
		std::cerr << "Listen " << std::endl;
		MainEvent *pMainEvent = static_cast<MainEvent*>(user_data);
		struct bufferevent *bev;
		bev = bufferevent_socket_new(pMainEvent->getBase(), fd, BEV_OPT_CLOSE_ON_FREE);
		if(!bev) {
			std::cerr << "Error constructing bufferevent!" << std::endl;
			event_base_loopbreak(pMainEvent->getBase());
			return;
		}
		pMainEvent->ListenHandle(bev, sa, socklen);
	}

	struct event_base* MainEvent::gEventBase = NULL;

	void MainEvent::InstanceEventBase() {
		if(NULL == MainEvent::gEventBase)
		{
			MainEvent::gEventBase = event_base_new();
		}
	}	
	struct event_base* MainEvent::GetGlobalEventBase()
	{
		return MainEvent::gEventBase;
	}	
}











