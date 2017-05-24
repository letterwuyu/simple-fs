#ifndef _CLIENT_EVENT_H__
#define _CLIENT_EVENT_H__
#include "../../common/net/package_analysis.h"
#include "../../common/net/libevent_socket.h"
#include "common_package.h"

using namespace net;

class ClientEvent public:SocketEvent, public PackageAnalysis{
public:
	typedef void (*HandleType)(void*);
	ClientEvent(HandleType handle);
	~ClientEvent();
private:
	void HandleNetPack(void* header);
	HandleType handle_;
public:
	virtual void ReadHandle(struct bufferevent *bev) override;
	virtual void WriteHandle(struct bufferevent *bev) override;
 	virtual void EventHandle(struct bufferevent *bev) override;
};
#endif //_CLIENT_EVENT_H__
