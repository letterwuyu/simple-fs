#ifndef _SERVER_MANAGER_H__
#define _SERVER_MANAGER_H__

#include <list>

#include "gate_event.h"

struct ServerInfo
{
	GateEvent* socket_event_;
	int server_id_;
};

class ServerManager {
public:
	typedef std::list<ServerInfo*> ServerList;
	ServerManager() = default;
	~ServerManager();
	void 					AddServer(ServerInfo& info);
	void 					DeleteServer(int32_t server_id);
	ServerInfo*		 		SelectServer();
private:
	ServerList servers_;
};

#endif //_SERVER_MANAGER_H__
