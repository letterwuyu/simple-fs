#include "gate_event.h"

GateEvent::GateEvent(GateEvent::HandleType handle):
	SocketEvent(), PackageAnalysis(handle, this){}

GateEvent::~GateEvent() {}

void GateEvent::ReadHandle(struct bufferevent *bev)
{
	struct evbuffer *input =bufferevent_get_input(bev);
    size_t sz=evbuffer_get_length(input);	
    if (sz> 0)
    {	
		char* buffer = new char[sz];
		memset(buffer, 0, sz);
    	bufferevent_read(bev, buffer, sz);
		TcpDataSplit(buffer, sz);
		delete buffer;
    }
}

void GateEvent::WriteHandle(struct bufferevent *bev)
{
}

void GateEvent::EventHandle(struct bufferevent *bev)
{
}

