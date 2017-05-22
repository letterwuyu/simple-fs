#ifndef VIRTUAL_VOLUME_H
#define VIRTUAL_VOLUME_H
#include "global.h"
#include "StorageManager.h"

class VirtualVolume {
public:
	typedef std::list<ServerInfo*> ServerList;
	VirtualVolume() = default;
	bool 					AddServer(ServerInfo* server)
	bool 					DeleteServer(int32_t server_id);
	const ServerList        GetServerList();
private:
	ServerList servers_;
};
#endif //VIRTUAL_VOLUME_H
