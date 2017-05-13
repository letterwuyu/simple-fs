#ifndef VIRTUAL_VOLUME_MANAGER
#define VIRTUAL_VOLUME_MANAGER
#include "virtual_volume.h"
#include "../common/imp/singleton.h"
#include "../common/def/def.h"
#include "../commom/log4z/log4z.h"
#include <chrono>
#include <vector>
#include <map>
using namespace imp;	
using namespace std::chrono;

class VirtualVolumeManger {
public:
	uint64 CreateVirtualVolume()
	{
		if(Singletion<StorageManager>::instance.ServerNum == 0)
			return 0;
		uint64 volume_id = system_clock::now().since_time_epoch().count();
		VirtualVolume virtual_volume(volume_id);
		virtual_volume.AddStorage(Singletion<StorageManager>::instance.SelectServer());
		LOGINFO("create virtual volume id = " << volume_id);
	}

	void DeleteVirtualVolume(volume_id)
	{
		for(auto it = virtual_volumes_.begin(), it != virtual_volumes_.end(); ++it)
		{
			if(it.GetVolumeId() == volume_id)
			{
				it = virtual_volumes_.erase(it);
			}
		}
	}

	std::vector<VirtualVolume>& GetList()
	{
		return virtual_volumes_;
	}
private:
	std::vector<VirtualVolume> virtual_volumes_;
	std::multimap<std::string, uint64> server_volume_map_;
	std::multimap<uint64, std::string> volume_server_map_;
};
#define //VIRTUAL_VOLUME_MANAGER
