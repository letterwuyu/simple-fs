#include "data_server_manager.h"

DataServerManager::DataServerManager():
	server_map_(map<int, SocketEvent*>()), servers(vector<sint32>()) {}

DataServerManager::~DataServerManager() {}

bool DataServerManager::AddServer(sint32 server_id, SocketEvent* server)
{
	servers_.push_back(server_id);
    server_map_.insert(make_pair(server_id, server));
    return true;
}

bool DataServerManager::DeleteServer(sint server_id)
{
	server_map_.erase(server_id);
    servers_.erase(server_id);
}

SocketEvent* DataServerManager::GetServer(sint32 server_id)
{
	auto it = server_map_.find(server_id);
    if(it != server_map_.end())
    	return it->second;
   	return NULL;
}

vecetor<sint32>& DataServerManager::GetServers()
{
	return servers_;
}
