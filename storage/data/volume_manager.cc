#include "volume_manager.h"

VolumeManager::VolumeManager():volume_map_(VolumeManager::VolumeMap()) {}

VolumeManager::~VolumeManager()
{
	for(auto it = volume_map_.begin(); it != volume_map_.end(); ++it)
	{
		if(NULL != it->second)
			delete it->second;
	}
}

Volume* VolumeManager::CreateVolume(const std::string& volume_name)
{
	std::hash<std::string> hash_fn;
	uint64 volume_id = hash_fn(volume_name);
	Volume* vp = new Volume(volume_name, volume_id);
	if(NULL == vp)
	{
		LogError("VolumeManager::CreateVolume NULL == vp");
		return NULL;
	} 
	CSingle(DBManager).Put(volume_name, std::to_string(volume_id));
	CSingle(DBManager).Put(std::to_string(volume_id), std::string());
	return vp;
}

Volume* VolumeManager::GetVolume(uint64 volume_id)
{
	auto it = volume_map_.find(volume_id);
	if(volume_map_.end() == it)
	{
		LogError("VolumeManager::GetVolume volume_map_.end()");
		return NULL;
	}
	if(NULL == it->second)
	{
		LogError("VolumeManager::GetVolume NULL == it->second");
		return NULL;
	}
	return it->second;
}

bool VolumeManager::DeleteVolume(uint64 volume_id)
{
	auto it = volume_map_.find(volume_id);
	if(volume_map_.end() == it)
    {
        LogError("VolumeManager::GetVolume volume_map_.end()");
        return false;
    }
    if(NULL == it->second)
    {
        LogError("VolumeManager::GetVolume NULL == it->second");
		volume_map_.erase(it);
        return false;
    }
	it->second->Delete();
	CSingle(DBManager).Delete(std::to_string(volume_id));
    volume_map_.erase(it);
	return true;
}


















