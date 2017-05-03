#include "clinet_process"
#include "client_service.h"

ServiceEvent::ServiceEvent(struct bufferevent* bev, ServiceEvent::HandleType handle):
	net::SocketEvent(bev), package_analysis_(handle) {}

ServiceEvent::~ServiceEvent() {}

void ServiceEvent::ReadHandle(struct bufferevent* bev)
{
	struct evbuffer *input = bufferevent_get_input(bev);
	size_t sz = evbuffer_get_length(input);
	char* buffer = new char[sz]();
	memset(buffer, 0, sz);
	if(sz > 0)
	{
		bufferevent_read(bev, buffer, sz);
		package_analysis_.TcpDataSplit(buffer, sz);
	}
}

void ServiceEvent::ReadHandle(struct bufferevent* bev)
{
}

void ServiceEvent::EventHandle(struct bufferevent* bev)
{
}
