#include "storage_manager.h"
#include "../../common/def/def.h"
#include "../../common/log4z/log4z.h"

ServerManager::~ServerManager()
{
	for(auto it = servers_.begin(); it != servers_.end(); ++it)
	{
		if(nullptr != (*it))
			delete *it;
	}
}

void ServerManager::AddServer(ServerInfo& info)
{
	ServerInfo* server_info = new ServerInfo;
	if(nullptr == server_info)
	{
		LogError("ServerManager::AddServer nullptr == server_info");
		return;
	}
	*server_info = info;
	servers_.push_back(server_info);
}

void ServerManager::DeleteServer(int server_id)
{
	for(auto it = servers_.begin(); it != servers_.end(); ++it)
	{
		if(nullptr == *it)
			continue;
		if((*it)->server_id_ == server_id)
		{
			delete *it;
			servers_.erase(it);
			break;
		}
	}
}

ServerInfo* ServerManager::SelectServer()
{
	if(servers_.empty())
		return nullptr;
	return *servers_.begin();
}








