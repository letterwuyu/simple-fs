#ifndef _Gate_EVENT_H__
#define _Gate_EVENT_H__
#include "../../common/net/package_analysis.h"
#include "../../common/net/libevent_socket.h"

using namespace net;

class GateEvent : public SocketEvent, public PackageAnalysis{
public:
//    typedef void (*HandleType)(void*);
    GateEvent(HandleType handle);
    ~GateEvent();
public:
    virtual void ReadHandle(struct bufferevent *bev) override;
    virtual void WriteHandle(struct bufferevent *bev) override;
    virtual void EventHandle(struct bufferevent *bev) override;
};
#endif //_Gate_EVENT_H__
