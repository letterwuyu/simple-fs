#ifndef _MONGODB_CXX_MANAGER_H__
#define _MONGODB_CXX_MANAGER_H__
#include "mongodb_manager.h"
#include <string>

class MongoDBCXXManager {
public:
	MongoDBCXXManager();
	~MongoDBCXXManager();
	MongoDBManager& GetVirtualDB();
	MongoDBManager& GetDB();
private:
	MongoDBManager virtual_db_;
	MongoDBManager db_;	
};

#endif //_MONGODB_CXX_MANAGER_H__
