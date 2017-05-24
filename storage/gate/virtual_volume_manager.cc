#include "virtual_volume_manager.h"

VirtualVolumeManager::VirtualVolumeManager():
	virtual_volume_map_(VirtualVolumeManager::VirtualVolumeMap ()){}

VirtualVolumeManager::~VirtualVolumeManager() {}

VirtualVolume* VirtualVolumeManager::CreateVirtualVolume(const std::string& virtual_volume_name)
{
/*
	vector<uint64> servers = singleton<DataServerManager>::intance().GetServers();
   	if(servers.empty)
      	return 0;
    SocketEvent* se = singleton<DataServerManager>::intance().GetServer(servers[0]);
    if(NULL == se)
       return 0;
                
    uint64 volume_id = steady_clock::now().time_since_epoch().count();
    ostringstream vos;
    vos << "virtual_volume_"<< volume_id;
    ostringstream sos;
    sos << servers[0];
    singleton<DBManager>::instance().Put(vos.str(), sos.str());
    shared_ptr<VirtualVolume> sp = maked_shared<VirtualVolume>(VirtualVolume);
    sp->AddServer(servers[0]);
                
    CONSTRUCT_MESSAGE(GD_CreateVolume);
    msg.volume_info_.volume_id_ = volume_id;
    se->Write(reinterpret_cast<char*>(&msg), sizeof(msg));
                
    virtual_volume_map_.insert(make_pair(volume_id, sp));
    return volume_id;
*/
	ServerInfo* server = GSingle(DataManager).SelectServer();
	if(nullptr == server)
	{
		LogError("VirtualVolumeManager::CreateVirtualVolume nullptr == gate_event");
		return false;
	}
	VirtualVolume* virtual_volume = new VirtualVolume;
	if(nullptr == virtual_volume)
	{
		LogError("VirtualVolumeManager::CreateVirtualVolume nullptr == virtual_volume");
		return false; 
	}
	virtual_volume->AddServer(server);
	return virtual_volume;
}

VirtualVolume* VirtualVolumeManager::GetVirtualVolume(const std::string& virtual_volume_name)
{   
	auto it = virtual_volume_map_.find(virtual_volume_name);
    if(virtual_volume_map_.end() == it)
	{
		LogError("VirtualVolumeManager::GetVirtualVolume virtual_volume_map_.end() == it");
		return nullptr;
	}
	return it->second;
}   

