#ifndef _MONGODB_CXX_MANAGER_H__
#define _MONGODB_CXX_MANAGER_H__
#include "mongodb_manager.h"

class MongoDBCXXManager {
public:
	MonogDBCXXManager();
	~MongoDBCXXManager();
	MongoDBManager& GetVirtualDB();
	MongoDBManager& GetDB();
private:
	MongoDBManager virtual_db_;
	MongoDBManager db_;
};

#endif //_MONGODB_CXX_MANAGER_H__
