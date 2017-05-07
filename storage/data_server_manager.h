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
	DataServerManager();
	~DataServerManager();
	bool AddServer(sint32 server_id, SocketEvent* server)
	bool DeleteServer(sint server_id)
	SocketEvent* GetServer(sint32 server_id)
	vecetor<sint32>& GetServers()
private:
	map<sint32, SocketEvent*> server_map_;	
	vector<sint32> servers_;
};

#endif //DATA_SERVER_MANAGER_H
















