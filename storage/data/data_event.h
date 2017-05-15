#ifndef _DATA_EVENT_H__
#define _DATA_EVENT_H__
#include "../../common/net/package_analysis.h"
#include "../../common/net/libevent_socket.h"
#include "common_package.h"

using namespace net;

class DataEvent public:SocketEvent, public PackageAnalysis{
public:
	typedef void (*HandleType)(void*);
	DataEvent(HandleType handle);
	~DataEvent();
private:
	void HandleNetPack(void* header);
	HandleType handle_;
public:
	virtual void ReadHandle(struct bufferevent *bev) override;
	virtual void WriteHandle(struct bufferevent *bev) override;
 	virtual void EventHandle(struct bufferevent *bev) override;
};
#endif //_DATA_EVENT_H__
