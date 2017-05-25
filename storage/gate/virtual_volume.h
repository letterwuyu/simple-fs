#ifndef _VIRTUAL_VOLUME_H__
#define _VIRTUAL_VOLUME_H__
#include "global.h"
#include "StorageManager.h"

class VirtualVolume {
public:
	typedef std::list<ServerInfo*> ServerList;
	VirtualVolume() = default;
	bool 					AddServer(ServerInfo* server)
	bool 					DeleteServer(int server_id);
	const ServerList        GetServerList();
private:
	ServerList servers_;
};
#endif //_VIRTUAL_VOLUME_H__
