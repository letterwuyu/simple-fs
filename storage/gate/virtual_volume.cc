#include"virtual_volume.h"

bool VirtualVolume::AddServer(ServerInfo* server)
{
	servers_.push_back(server);
	return true;
}

bool VirtualVolume::DeleteServer(int server_id)
{
	for(auto it = servers_.begin(); it != servers_.end(); ++it)
	{
		if(nullptr == *it)
			continue;
		if((*it)->server_id_ == server_id)
		{
			servers_.erase(it);
			return true;
		}
	}
	return true;
}

const VirtualVolume::ServerList VirtualVolume::GetServerList() const
{
	return servers_;
}

