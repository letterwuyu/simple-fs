#ifndef VIRTUAL_VOLUME_H
#define VIRTUAL_VOLUME_H
#include "global.h"

class VirtualVolume {
public:
	VirtualVolume();
	bool SetVolumeId(uint64 volume_id)
	{
		volume_id_;
		return true;		
	}
	bool AddServer(uint64 server_id)
	{
		servers_id_.push_back(server_id);
		return true;
	}
	vector<uint64>& GetServers()
	{
		return servers_id_;
	}
private:
	vector<uint64> servers_id_;
	uint64 volume_id_;
};
#endif //VIRTUAL_VOLUME_H
