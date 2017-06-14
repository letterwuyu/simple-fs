#ifndef _SERVER_INFO_H__
#define _SERVER_INFO_H__

#include "client_event.h"

enum ServerType
{
	Gate,
	Data,
};

struct ServerInfo
{
	ClientEvent* client_event_;
	uint32_t     id_;
	ServerType   type;
};

#endif //_SERVER_INFO_H__
