#ifndef DB_MANAGER_H
#define DB_MANAGER_H
#include <string.h>
#include <iostream>
#include <leveldb/db.h>

class DBManager {
public:
	DBManager()
	{
		leveldb::Options options;
		options.create_if_missing = true;
		status = leveldb::DB::Open(options, "./db", &db);
		assert(status.ok());
	}
	~DBManager()
	{
		delete *db;
	}

	void Put(const std::string& key, const std::string& value)
	{
		status = db->Put(leveldb::WriteOptions(), key, &value);
		assert(status.ok());
	}

	bool Get(const std::string& key, std::string& value)
	{
		status = db->Get(leveldb::ReadOptions(), key, &value);
;
		if(!status.ok()) return false;
		return true;
	}

	void Delete(const std::string& key)
	{
		status = db->Delete(leveldb::WriteOptions(), key);
		assert(status.ok());
	}
private:
	leveldb::DB* db;
	leveldb::Status status;	
};
#endif //DB_MANAGER_H
