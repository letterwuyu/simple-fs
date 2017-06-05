#include "data_event.h"
#include <iostream>
DataEvent::DataEvent(DataEvent::HandleType handle):
	SocketEvent(), PackageAnalysis(handle, this) {}

DataEvent::~DataEvent() {}

void DataEvent::ReadHandle(struct bufferevent *bev)
{
	std::cerr << "DataEvent::ReadHandle " << std::endl;
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

void DataEvent::WriteHandle(struct bufferevent *bev)
{
}

void DataEvent::EventHandle(struct bufferevent *bev)
{
}
