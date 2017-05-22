#include "mongodb_manager.h"
#include "../log4z/log4z.h"

#include <chrono>

MongoDBManager::MongoDBManager(const std::string& db_name)
	:db_name_(db_name), inst_(mongocxx::instance{}), conn_(mongocxx::client{mongocxx::uri{}})
{
	collections_.insert(std::make_pair(VirtualVolume, std::string("VirtualVolume")));
	collections_.insert(std::make_pair(Volume, std::string("Volume")));
}

MongoDBManager::~MongoDBManager() {}

#if 0
bool MongoDBManager::CreateVirtualVolume(const std::sting& virtual_volume_name)
{
	std::hash<std::string> hash_fn;
	uint64_t virtual_volume_id = hash_fn(virtual_volume_name);
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
 	uint64_t virtual_volume_id = hash_fn(virtual_volume_name);
	builder::stream::document delete_doc;
	deletc_doc << "_id" << virtual_volume_id
			   << "name" << virtual_volume_name;
	auto collection = conn_[collections_[VolumeVirtual]];
	collection.delete_one(delete_doc.view())'
	LogInfo("delete virtual volume : " << virtual_volume_name);
	return true;
}
#endif

bool MongoDBManager::CreateServerForVirtual(const std::string& virtual_volume_name, int server_id)
{
	builder::stream::document build_doc;
	build_doc << "name" << virtual_volume_name
              << "servers" << server_id;
	auto collection = conn_[collections_[VolumeVirtual]];
    collection.insert_one(build_doc.view());
    LogInfo("MongoDBManager::CreateServerForVirtual add server : " << server << "for virtual_volume" << virtual_volume_name);
    return true;
}

bool MongoDBManager::DeleteServerForVirtual(const std::string& virtual_volume_name, int server_id)
{
	builder::stream::document delete_doc;
    delete_doc << "name" << virtual_volume_name
              << "servers" << server_id;
    auto collection = conn_[collections_[VolumeVirtual]];
    collection.delete_one(delete_doc.view());
    LogInfo("MongoDBManager::CreateServerForVirtual delete server : " << server << "from virtual_volume" << virtual_volume_name);
    return true;
}

bool MongoDBManager::AddUnitForVolume(const std::string& volume_name, uint64_t& unit_id)
{
	builder::stream::document build_doc;
    build_doc << "name" << volume_name
              << "unit" << unit_id;
    auto collection = conn_[collections_[Volume]];
    collection.insert_one(build_doc.view());
    LogInfo("MongoDBManager::AddUnitForVolume add unit : " << unit_id << "for volume" << volume_name);
    return true;
}

bool MongoDBManager::GetUnitForVolume(const std::string& volume_name, std::vector<uint64_t>& uints)
{
	builder::stream::document build_doc;
    build_doc << "name" << volume_name << finalize;
    auto collection = conn_[collections_[Volume]];
    auto cursor = collection.find(build_doc);
	for(auto&& doc : cursor)
		units.push_back(bsoncxx::to_json(doc)[volume_name]);
    return true;
}
