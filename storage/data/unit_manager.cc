#include "unit_manager.h"
#include "../../common/db/leveldb_manager.h"
#include "../../common/imp/singleton.h"
#include "../../common/def/def.h"
#include "../../common/log4z/log4z.h"

#include <chrono>
#include <string>

using namespace imp;

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
	long long unit_id = std::chrono::steady_clock::now().time_since_epoch().count();
	/*
	std::stringstream oskey;
	oskey << unit_id;
	std::ostringstream osvalue;
	osvalue
	osvalue << "./storage/" << unit_id;
	GSingle(LevelDBManager).Put(oskey.str(), osvalue.str());
	*/
	GSingle(LevelDBManager)->CreateUnit(unit_id);
	Unit* punit = new Unit(std::to_string(unit_id), unit_id);
	unit_map_.insert(std::make_pair(unit_id, punit));
	punit->Create();
	return punit;
}

bool UnitManager::DeleteUnit(long long unit_id)
{
	auto it = unit_map_.find(unit_id);
	if(it == unit_map_.end())
	{
		LogError("UnitManager::DeleteUnit it = unit_map_.end");
		return false;
	}
	if(NULL == it->second)
	{
		LogError("UnitManager::DeleteUnit NULL == it->second");
		return false;
	}
	
	GSingle(LevelDBManager)->DeleteUnit(it->second->GetId());
	it->second->Delete();
	delete it->second;
	unit_map_.erase(it);
	return true;
}

void UnitManager::LoadUnitForMongoDB(void)
{
	/*
  	std::vector<std::string> volumes;
	GSingle(MongoDBCXXManager)->GetVirtualDB().GetVolumeList(volumes);
	for(auto it = volumes.begin(); it != volumes.end(); ++it)
	{
		Volume* volume = new Volume(*it);
		std::vector<long long> units;
		GSingle(MongoDBCXXManager)->GetDB().GetUnitForVolume(*it, units);
		for(auto it = units.begin(); it != units.end(); ++it)
		{
			volume->AddUnit(*it);
		}
	}
	*/
}

Unit* UnitManager::CreateUnit(long long id)
{
	Unit* unit = new Unit(std::to_string(id), id);
	if(nullptr != unit)
	{
		unit_map_.insert(std::make_pair(id, unit));
	}
	return unit;
}















