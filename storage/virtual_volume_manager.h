#ifndef VIRTUAL_VOLUMME_MANAGER_H
#define VIRTUAL_VOLUMME_MANAGER_H
#include "global.h"
#include "dbmanager.h"

class VirtualVolumeManager {
public:
	uint64 CreateVirtualVolume()
	{
		vector<uint64> servers = singleton<DataServerManager>::intance().GetServers();
		if(servers.empty)
			return 0;
		SocketEvent* se = singleton<DataServerManager>::intance().GetServer(servers[0]);
		if(NULL == se)
			return 0;
		
		uint64 volume_id steady_clock::now().time_since_epoch().count();
		ostringstream vos;
		vos << "virtual_volume "<< volume_id;
		ostringstream sos;
		sos << servers[0];
		singleton<DBManager>::instance().Put(os.str(), sos.str());
		shared_ptr<VirtualVolume> sp = maked_shared<VirtualVolume>(VirtualVolume);
		sp->AddServer(servers[0]);
		
		CONSTRUCT_MESSAGE(GD_CreateVolume);
		msg.volume_info_.volume_id_ = servers[0];
		se->Write(reinterpret_cast<char*>(&msg), sizeof(msg));
		
		virtual_volume_map_.insert(make_pair(volume_id, sp));
		return volume_id;
	}

	shared_ptr<VirtualVolume>& GetVirtualVolume(uint64 volume_id)
	{
		auto it = virtual_volume_map_.find(volume_id);
	//	if(it != virtual_volume_map_.end())
			return it->second;
	}

	AddVolumeServer(uint64 volume_id, uint64 server_id)
	{				
	}

private:
	map<uint64, shared_ptr<VirtualVolume> > virtual_volume_map_;	
};
#endif //VIRTUAL_VOLUMME_MANAGER_H
