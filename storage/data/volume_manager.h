#ifndef VOLUME_MANAGER_H
#define VOLUME_MANAGER_H

class VolumeManager {
public:
	typedef std::unordered_map<uint64, Volume*> VolumeMap;
	VolumeManager();
	~VolumeManager();
	Volume*	CreateVolume(const std::string& volume_name);
	Volume* GetVolume(const std::string& volume_name);
	Volume* GetVolume(uint64 volume_id);
	bool    DeleteVolume(const std::string& volume_name);
	bool    Loadvolume();
private:
	VolumeMap volume_map_;
};
#endif //VOLUME_MANAGER_H
