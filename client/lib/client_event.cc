#include "client_event.h"

ClientEvent::ClientEvent(ClientEvent::HandleType handle):
	handle_(handle), SocketEvent(), PackageAnalysis(/*handle*/) {}

ClientEvent::~ClientEvent() {}

void ClientEvent::ReadHandle(struct bufferevent *bev)
{
	struct evbuffer *input =bufferevent_get_input(bev);
    sz=evbuffer_get_length(input);	
    if (sz> 0)
    {	
		char* buffer = new char[sz];
		memset(buffer, 0, sz);
    	bufferevent_read(bev,buf,sz);
		TcpClientSplit(buffer, sz);
		delete buffer;
    }
}

void ClientEvent::WriteHandle(struct bufferevent *bev)
{
}

void ClientEvent::EventHandle(struct bufferevent *bev)
{
}

void ClientEvent::HandleNetPack(void *header)
{
	CommonPackage pack(this, header);
	handle_(&pack);	
}

