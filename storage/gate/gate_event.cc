#include "data_event.h"

GateEvent::GateEvent(GateEvent::HandleType handle):
	handle_(handle), SocketEvent(), PackageAnalysis(/*handle*/) {}

GateEvent::~GateEvent() {}

void GateEvent::ReadHandle(struct bufferevent *bev)
{
	struct evbuffer *input =bufferevent_get_input(bev);
    sz=evbuffer_get_length(input);	
    if (sz> 0)
    {	
		char* buffer = new char[sz];
		memset(buffer, 0, sz);
    	bufferevent_read(bev,buf,sz);
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

void GateEvent::HandleNetPack(void *header)
{
	CommonPackage pack(this, header);
	handle_(&pack);	
}

