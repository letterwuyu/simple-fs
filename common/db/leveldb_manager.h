#ifndef LEVELDB_MANAGER_H
#define LEVELDB_MANAGER_H
#include <string.h>
#include <iostream>
#include <leveldb/db.h>

class LevelDBManager {
public:
	LevelDBManager();
	~LevelDBManager();

	void Put(const std::string& key, const std::string& value);
	bool Get(const std::string& key, std::string& value);
	void Delete(const std::string& key)
private:
	leveldb::DB* db;
	leveldb::Status status;	
};
#endif //LEVELDB_MANAGER_H
