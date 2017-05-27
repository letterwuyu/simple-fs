#include "leveldb_manager.h"

LevelDBManager::LevelDBManager()
{
	leveldb::Options options;
    options.create_if_missing = true;
    status_ = leveldb::DB::Open(options, "./db", &db_);
    assert(status_.ok());
}

LevelDBManager::~LevelDBManager()
{
	 delete db_;
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

bool LevelDBManager::CreateUnit(int unit_id)
{
	status_ = db_->Put(leveldb::WriteOptions(), std::to_string(unit_id), std::to_string(unit_id));
	return status_.ok();
}

bool LevelDBManager::DeleteUnit(int unit_id)
{
	status_ = db_->Delete(leveldb::WriteOptions(), std::to_string(unit_id));
	return status_.ok();
}















