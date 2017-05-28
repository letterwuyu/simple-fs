#ifndef _VIRTUAL_VOLUME_H__
#define _VIRTUAL_VOLUME_H__

#include <string>
#include "storage_manager.h"

class VirtualVolume {
public:
	typedef std::list<ServerInfo*> ServerList;
	VirtualVolume(const std::string& name);
	~VirtualVolume();
	bool 					AddServer(ServerInfo* server);
	bool 					DeleteServer(int server_id);
	const ServerList        GetServerList() const;
	const std::string& GetName(void) const;
private:
	ServerList servers_;
	std::string name_;
};
#endif //_VIRTUAL_VOLUME_H__
