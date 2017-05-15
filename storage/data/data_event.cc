#include "data_event.h"

DataEvent::DataEvent(DataEvent::HandleType handle):
	handle_(handle), SocketEvent(), PackageAnalysis(/*handle*/) {}

DataEvent::~DataEvent() {}

void DataEvent::ReadHandle(struct bufferevent *bev)
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

void DataEvent::WriteHandle(struct bufferevent *bev)
{
}

void DataEvent::EventHandle(struct bufferevent *bev)
{
}

void DataEvent::HandleNetPack(void *header)
{
	CommonPackage pack(this, header);
	handle_(&pack);	
}







