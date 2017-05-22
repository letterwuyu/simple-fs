#include "dbmanager.h"

LevelDBManager::LevelDBManager()
{
	leveldb::Options options;
    options.create_if_missing = true;
    status = leveldb::DB::Open(options, "./db", &db);
    assert(status.ok());
}

LevelDBManager::~LevelDBManager()
{
	 delete *db;
}

/*
void LevelDBManager::Put(const std::string& key, const std::string& value)
{   
	status = db->Put(leveldb::WriteOptions(), key, &value);
    assert(status.ok());
}

bool LevelDBManager::Get(const std::string& key, std::string& value)
{   
	status = db->Get(leveldb::ReadOptions(), key, &value);
	if(!status.ok()) return false;
	return true;
}

void LevelDBManager::Delete(const std::string& key)
{
	status = db->Delete(leveldb::WriteOptions(), key);
	assert(status.ok());
}
*/

bool LevelDBManager::CreateUnit(uint64_t unit_id)
{
	status_ = db_->Put(leveldb::WriteOptions(), std::to_string(unit_id), std::to_string(unit_id));
	return status_.ok();
}

bool LevelDBManager::DeleteUnit(uint64_t unit_id)
{
	status_ = db_->Delete(leveldb::WriteOptions(), std::to_string(unit_id));
	return status_.ok();
}















