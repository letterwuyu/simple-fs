#ifndef _VOLUME_MANAGER_H__
#define _VOLUME_MANAGER_H__

#include <unordered_map>
#include <string>
#include "volume.h"

class VolumeManager {
public:
	typedef std::unordered_map<std::string, Volume*> VolumeMap;
	VolumeManager();
	~VolumeManager();
	Volume*	CreateVolume(const std::string& volume_name);
	Volume* GetVolume(const std::string& volume_name);
	Volume* GetVolume(int volume_id);
	bool    DeleteVolume(const std::string& volume_name);
	void    LoadVolume();
private:
	VolumeMap volume_map_;
};
#endif //_VOLUME_MANAGER_H__
