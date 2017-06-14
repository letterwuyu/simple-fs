#include "volume_manager.h"
#include "volume.h"
#include "../../common/def/def.h"
#include "../../common/log4z/log4z.h"
#include "../../common/imp/singleton.h"
#include "../../common/db/mongodb_cxx_manager.h"
#include "unit_manager.h"
#include <set>

using namespace imp;

VolumeManager::VolumeManager():volume_map_(VolumeManager::VolumeMap()) {}

VolumeManager::~VolumeManager()
{
	for(auto it = volume_map_.begin(); it != volume_map_.end(); ++it)
	{
		if(nullptr != it->second)
			delete it->second;
	}
}

Volume* VolumeManager::CreateVolume(const std::string& volume_name)
{
	std::hash<std::string> hash_fn;
	int volume_id = hash_fn(volume_name);
	
	std::cerr << "--" << volume_name << "--" << std::endl;

	Volume* vp = new Volume(volume_name, volume_id);
	if(nullptr == vp)
	{
		LogError("VolumeManager::CreateVolume nullptr == vp");
		return nullptr;
	}
	//此时执行create函数，正式为volume创建第一个unit并存入MongoDB
	if(!vp->Create())
	{
		LogError("VolumeManager::CreateVolume create volume fail");
		return nullptr;
	}
	volume_map_.insert(std::make_pair(volume_name, vp));
	return vp;
}

Volume* VolumeManager::GetVolume(const std::string& volume_name)
{
/*	 std::hash<std::string> hash_fn;
     uint64 volume_id = hash_fn(volume_name);
	 return GetVolume(volume_id);
*/
	std::cout << "++" << volume_name << "++" << std::endl;
	auto it = volume_map_.find(volume_name);
	if(volume_map_.end() == it)
	{
		LogError("VolumeManager::GetVolume volume_map_.end() == it");
		return nullptr;
	}
	if(nullptr == it->second)
	{
		LogError("VolumeManager::GetVolume nullptr == it->second");
		return nullptr;
	}
	return it->second;
}

Volume* VolumeManager::GetVolume(int volume_id)
{
/*	auto it = volume_map_.find(volume_id);
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
*/
	return nullptr;
}

bool VolumeManager::DeleteVolume(const std::string& volume_name)
{
	
//	std::hash<std::string> hash_fn;
//   uint64 volume_id = hash_fn(volume_name);
	auto it = volume_map_.find(volume_name);
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
    volume_map_.erase(it);
	return true;
}

void VolumeManager::LoadVolume()
{
	std::set<std::string> volumes;
	GSingle(MongoDBCXXManager)->GetVirtualDB().GetVolumeList(volumes);
	for(auto it = volumes.begin(); it != volumes.end(); ++it)
	{
		std::vector<long long> units;
		GSingle(MongoDBCXXManager)->GetDB().GetUnitForVolume(*it, units);
		std::hash<std::string> hash_fn;
		long long volume_id = hash_fn(*it);
		Volume* volume = new Volume(*it, volume_id);
		if(nullptr == volume)
		{
			LogError("VolumeManager::LoadVolume nullptr == volume")
		}
		volume_map_.insert(std::make_pair(*it, volume));
		for(auto it = units.begin(); it != units.end(); ++it)
		{
			Unit* unit = GSingle(UnitManager)->CreateUnit(*it);
			if(nullptr == unit)
			{
				LogError("VolumeManager::LoadVolume nullptr == unit");
				break;
			}
			volume->AddUnit(unit);
		}	
	}
}
















