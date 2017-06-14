#include "client_event.h"

ClientEvent::ClientEvent(ClientEvent::HandleType handle):
	SocketEvent(), PackageAnalysis(handle, this) {}

ClientEvent::~ClientEvent() {}

void ClientEvent::ReadHandle(struct bufferevent *bev)
{
	struct evbuffer *input =bufferevent_get_input(bev);
    size_t sz=evbuffer_get_length(input);	
    if (sz> 0)
    {	
		char* buffer = new char[sz];
		memset(buffer, 0, sz);
    	bufferevent_read(bev,buffer,sz);
		TcpDataSplit(buffer, sz);
		delete buffer;
    }
}

void ClientEvent::WriteHandle(struct bufferevent *bev)
{
}

void ClientEvent::EventHandle(struct bufferevent *bev)
{
}
