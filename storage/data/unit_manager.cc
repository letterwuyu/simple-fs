#include "unit_manager.h"

UnitManager::UnitManager():unit_map_(UnitManager::UnitMap()){}

UnitManager::~UnitManager()
{
	for(auto it = unit_map_.begin(); it != unit_map_.end(); ++it)
	{
		delete it->second;
	}
}

Unit* UnitManager::CreateUnit()
{
	uint64 unit_id = steady_clock::now().time_since_epoch.count();
	std::stringstream oskey;
	oskey << unit_id;
	std::ostringstream osvalue;
	osvalue
	osvalue << "./storage/" << unit_id;
	GSingle(LevelDBManager).Put(oskey.str(), osvalue.str());
	Unit* punit = new unit(uos.str(), unit_id);
	unit_map_.insert(make_pair(unit_id, punit));
	punit->Create();
	return punit;
}

bool UnitManager::DeleteUnit(uint64 unit_id)
{
	auto it = unit_map_.find(unit_id);
	if(it = unit_map_.end())
	{
		LogError("UnitManager::DeleteUnit it = unit_map_.end");
		return false;
	}
	if(NULL == it->second)
	{
		LogError("UnitManager::DeleteUnit NULL == it->second");
		return false;
	}
	
	GSingle(LevelDBManager).Delete(it->GetId());
	it->second->Delete();
	delete it->second;
	unit_map_.erase(it);
	return true;
}



















