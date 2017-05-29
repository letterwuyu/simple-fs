#include "mongodb_manager.h"
#include "../log4z/log4z.h"
#include "../def/def.h"

#include <chrono>
#include <stdint.h>

mongocxx::instance MongoDBManager::inst_;

MongoDBManager::MongoDBManager(const std::string& db_name)
	:db_name_(db_name)//, inst_{}, conn_{mongocxx::uri{}}
{
	
	std::cerr << "---------------------------------------c1" << std::endl;
	collections_.insert(std::make_pair(Collection_VirtualVolume, std::string("VirtualVolume")));
	collections_.insert(std::make_pair(Collection_Volume, std::string("Volume")));
	std::cerr << "---------------------------------------c2" << std::endl;
//	inst_ = mongocxx::instance{};
	conn_ = mongocxx::uri{};
}

MongoDBManager::~MongoDBManager() {}

#if 0
bool MongoDBManager::CreateVirtualVolume(const std::sting& virtual_volume_name)
{
	std::hash<std::string> hash_fn;
	uint64_t_t virtual_volume_id = hash_fn(virtual_volume_name);
	builder::stream::document build_doc;
	build_doc << "_id" << virtual_volume_id 
			  << "name" << virtual_volume_name
			  << "servers" << open_array << close_array;
	
	auto collection = conn_[collections_[VolumeVirtual]];
	collection.insert_one(build_doc.view());
	LOGInfo("create virtual volume : " << virutal_volume_name);
	return true;
}

bool MongoDBManager::DeleteVirtualVolume(const std::strong virtual_volume_name)
{
	std::hash<std::string> hash_fn;
 	uint64_t_t virtual_volume_id = hash_fn(virtual_volume_name);
	builder::stream::document delete_doc;
	deletc_doc << "_id" << virtual_volume_id
			   << "name" << virtual_volume_name;
	auto collection = conn_[collections_[VolumeVirtual]];
	collection.delete_one(delete_doc.view());
	LogInfo("delete virtual volume : " << virtual_volume_name);
	return true;
}
#endif

bool MongoDBManager::CreateServerForVirtual(const std::string& virtual_volume_name, int server_id)
{
	builder::stream::document build_doc;
	build_doc << "name" << virtual_volume_name
              << "server" << std::to_string(server_id);
	auto collection = conn_[db_name_][collections_[Collection_VirtualVolume]];
    collection.insert_one(build_doc.view());
    LogInfo("MongoDBManager::CreateServerForVirtual add server : " << server_id << "for virtual_volume" << virtual_volume_name);
    return true;
}

bool MongoDBManager::DeleteServerForVirtual(const std::string& virtual_volume_name, int server_id)
{
	builder::stream::document delete_doc;
    delete_doc << "name" << virtual_volume_name
              << "server" << server_id;
    auto collection = conn_[db_name_][collections_[Collection_VirtualVolume]];
    collection.delete_one(delete_doc.view());
    LogInfo("MongoDBManager::CreateServerForVirtual delete server : " << server_id << "from virtual_volume" << virtual_volume_name);
    return true;
}

bool MongoDBManager::AddUnitForVolume(const std::string& volume_name, int unit_id)
{
	builder::stream::document build_doc;
    build_doc << "name" << volume_name
              << "unit" << std::to_string(unit_id);
    auto collection = conn_[db_name_][collections_[Collection_Volume]];
    collection.insert_one(build_doc.view());
    LogInfo("MongoDBManager::AddUnitForVolume add unit : " << unit_id << "for volume" << volume_name);
    return true;
}

bool MongoDBManager::GetUnitForVolume(const std::string& volume_name, std::vector<int>& units)
{
	builder::stream::document build_doc;
    build_doc << "name" << volume_name << finalize;
    auto collection = conn_[db_name_][collections_[Collection_Volume]];
    auto cursor = collection.find(build_doc.view());
	for(auto&& doc : cursor) {
		units.push_back(std::stoi(doc["unit"].get_utf8().value.to_string()));
	}		
    return true;
}

bool MongoDBManager::DelUnitForVolume(const std::string& volume_name, int unit_id)
{
	builder::stream::document delete_doc;
    delete_doc << "name" << volume_name
               << "unit" << std::to_string(unit_id);
    auto collection = conn_[db_name_][collections_[Collection_Volume]];
    collection.delete_one(delete_doc.view());
    LogInfo("MongoDBManager::DelUnitForVolume delete unit : " << unit_id << "from volume" << volume_name);
    return true;
	
}
