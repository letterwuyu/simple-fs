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

