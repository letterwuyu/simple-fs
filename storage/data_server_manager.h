#ifndef DATA_SERVER_MANAGER_H
#define DATA_SERVER_MANAGER_H

#include "../common/imp/singleton.h"
#include "../common/log/log4z.h"
#include "../common/net/libevent_socket.h"
#include "../common/def/def.h"
#include "dbmanager.h"

#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
using namespace std;

class DataServerManager {
public:
	DataServerManager() = default;
	~DataServerManager() = default;
	bool AddServer(int server_id, SocketEvent* server)
	{
		servers_.push_back(server_id);
		server_map_.insert(make_pair(server_id, server));
		return true;
	}
	bool DeleteServer(int server_id)
	{
		server_map_.erase(server_id);
		servers_.erase(server_id);
	}
	SocketEvent* GetServer(server_id)
	{
		auto it = server_map_.find(server_id);
		if(it != server_map_.end())
			return it->second;
		return NULL;
	}
	vecetor<int>& GetServers()
	{
		return servers_;
	}
private:
	map<int, SocketEvent*> server_map_;	
	vector<int> servers_;
};

#endif //DATA_SERVER_MANAGER_H
















