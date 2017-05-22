#ifndef _SERVER_MANAGER_H__
#define _SERVER_MANAGER_H__
#include <vector>
#include <random>
#include "../common/net/libevent_socket.h"

struct ServerInfo
{
	GateEvent* socket_event_;
	int32_t server_id;
};

class ServerManager {
public:
	typedef std::list<DataInfo*> ServerList;
	DataManager() = default;
	void 					AddServer(ServerInfo& info)
	void 					DeleteServer(int32_t server_id);
	const ServerInfo* 		SelectServer();
private:
	ServerList servers_;
};

#endif //_SERVER_MANAGER_H__
