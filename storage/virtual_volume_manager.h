#ifndef VIRTUAL_VOLUMME_MANAGER_H
#define VIRTUAL_VOLUMME_MANAGER_H
#include "global.h"
#include "dbmanager.h"

class VirtualVolumeManager {
public:
	VirtualVolumeManager();
	~VirtualVolumeManager();
	uint64 CreateVirtualVolume();
	shared_ptr<VirtualVolume>& GetVirtualVolume(uint64 volume_id);
private:
	typedef map<uint64, shared_ptr<VirtualVolume> > VirtualVolumeMap;
	VirtualVolumeMap virtual_volume_map_;	
};
#endif //VIRTUAL_VOLUMME_MANiAGER_H
