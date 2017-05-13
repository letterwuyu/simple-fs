#ifndef CLINET_SERVICE_H
#define CLIENT_SERVICE_H
#include "libevent_network.h"
#include "libevent_socket.h"
#include "common_thread.h"
#include "package_analysis.h"
#include "def"
#include <iostream>
#include <functional>
#include <vector>
#include <map>

class Reslove :: public PackageAnalysis {
public:
	Reslove() = default;
private: 
	bool HandleNetPack(void* control, void* package);
    bool Register();
};

class ServiceEvent : public net::SocketEvent {
public:

	ServiceEvent(struct bufferevent* bev, HandleType handle);
	ServiceEvent() = default;
	~ServiceEvent();
	virtual void ReadHandle(struct bufferevent *bev) override;
	virtual void WriteHandle(struct bufferevent *bev) override;
	virtual void EventHandle(struct bufferevent *bev) override;

	typedef void (*HandleType)(void*);
private:
	net::PackageAnalysis package_analysis_;
};


class ServiceMain : public net::MainEvent, public CommonThread {
public:
	ServiceMain();
	void ListenHandle(struct bufferevent *bev);
	void Run();
	typedef std::unordered_map<sint32, std::function<bool(void*, void*)>> HandleMap;
private:
	std::vector<ServiceEvent> services_;
	
};
#endif //CLIENT_SERVICE_H
