#ifndef DB_MANAGER_H
#define DB_MANAGER_H
#include <string.h>
#include <iostream>
#include <leveldb/db.h>

class DBManager {
public:
	DBManager();
	~DBManager();

	void Put(const std::string& key, const std::string& value);
	bool Get(const std::string& key, std::string& value);
	void Delete(const std::string& key)
private:
	leveldb::DB* db;
	leveldb::Status status;	
};
#endif //DB_MANAGER_H
