#ifndef _MONGODB_MANAGER_H__
#define _MONGODB_MANAGER_H__

#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>

#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/v_noabi/bsoncxx/builder/stream/helpers.hpp>

#include "../log4z/log4z.h"

using namespace std;

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using namespace bsoncxx;

enum Collection
{
	VirtualVolume,
	Volume
};

class MongoDBManager {
public:
	MongoDBManager(const std::string& db_name);
	~MongoDBManager();
public:
//	bool CreateVirtualVolume(const std::sting& virtual_volume_name);
//	bool DeleteVirtualVolume(const std::string virtual_volume_name);
	bool CreateServerForVirtual(const std::string& virtual_volume_name, int server_id);
	bool DeleteServerForVirtual(const std::string& virtual_volume_name, int server_id);
	bool AddUnitForVolume(const std::string& volume_name, int unit_id);
	bool GetUnitForVolume(const std::string& volume_name, std::vector<int>& units);
private:
	mongocxx::client conn_;
	mongocxx::instance inst_;
	std::string db_name_;
	std::unordered_map<int, std::string> collections_;
};
#endif //_MONGODB_MANAGER_H__
