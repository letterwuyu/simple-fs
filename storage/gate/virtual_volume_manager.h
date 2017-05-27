#ifndef _VIRTUAL_VOLUMME_MANAGER_H__
#define _VIRTUAL_VOLUMME_MANAGER_H__

#include <unordered_map>

#include "virtual_volume.h"

class VirtualVolumeManager {
public:
	VirtualVolumeManager();
	~VirtualVolumeManager();
	VirtualVolume* CreateVirtualVolume(const std::string& virtual_volume_name);
	VirtualVolume* GetVirtualVolume(const std::string& virtual_volume_name);
private:
	typedef std::unordered_map<std::string, VirtualVolume*> VirtualVolumeMap;
	VirtualVolumeMap virtual_volume_map_;
};
#endif //_VIRTUAL_VOLUMME_MANiAGER_H__
