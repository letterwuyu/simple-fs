#include"virtual_volume.h"

VirtualVolume::VirtualVolume():
	servers_id_(std::vector<uint64>()), volume_id_(0) {}

bool VirtualVolume::SetVolumeId(uint64 volume_id)
{   
	volume_id_;
	return true;    
}

bool VirtualVolume::AddServer(uint64 server_id)
{   
	servers_id_.push_back(server_id);
	return true;
}   

vector<uint64>& VirtualVolume::GetServers()
{   
	return servers_id_;
}   
