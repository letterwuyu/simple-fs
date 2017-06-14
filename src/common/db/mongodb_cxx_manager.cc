#include "mongodb_cxx_manager.h"

MongoDBCXXManager::MongoDBCXXManager():
	virtual_db_("virtual_volume_db"), db_("volume_db") {}

MongoDBCXXManager::~MongoDBCXXManager() {}

MongoDBManager& MongoDBCXXManager::GetVirtualDB()
{
	return virtual_db_;
}

MongoDBManager& MongoDBCXXManager::GetDB()
{
	return db_;
}
