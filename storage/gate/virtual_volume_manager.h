#ifndef VIRTUAL_VOLUMME_MANAGER_H
#define VIRTUAL_VOLUMME_MANAGER_H
#include "global.h"
#include "dbmanager.h"

class VirtualVolumeManager {
public:
	VirtualVolumeManager();
	~VirtualVolumeManager();
	bool CreateVirtualVolume(const std::string& virtual_volume_name);
	shared_ptr<VirtualVolume>& GetVirtualVolume(const std::string& virtual_volume_name);
private:
	typedef map<std::string, VirtualVolume*> VirtualVolumeMap;
	VirtualVolumeMap virtual_volume_map_;
};
#endif //VIRTUAL_VOLUMME_MANiAGER_H
