#ifndef _SERVER_MANAGER_H__
#define _SERVER_MANAGER_H__

#include <list>
#include <string>
#include "gate_event.h"

struct ServerInfo
{
	GateEvent* socket_event_;
	int server_id_;
	std::string listen_ip_;
	int listen_port_;
};

class ServerManager {
public:
	typedef std::list<ServerInfo*> ServerList;
	ServerManager() = default;
	~ServerManager();
	void 					AddServer(ServerInfo& info);
	void 					DeleteServer(int32_t server_id);
	ServerInfo*		 		SelectServer();
	ServerInfo*             GetServer(int32_t server_id);
private:
	ServerList servers_;
};

#endif //_SERVER_MANAGER_H__
