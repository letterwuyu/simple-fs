#ifndef _VIRTUAL_VOLUME_H__
#define _VIRTUAL_VOLUME_H__

#include "storage_manager.h"

class VirtualVolume {
public:
	typedef std::list<ServerInfo*> ServerList;
	VirtualVolume() = default;
	bool 					AddServer(ServerInfo* server);
	bool 					DeleteServer(int server_id);
	const ServerList        GetServerList() const;
private:
	ServerList servers_;
};
#endif //_VIRTUAL_VOLUME_H__
