#include "unit.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "../../common/db/leveldb_manager.h"
#include "../../common/def/def.h"
#include "../../common/imp/singleton.h"
//#include "../../common/db/leveldb_manager.h"

using namespace imp;

Unit::Unit(const std::string& name, int id): name_(name), id_(id), size_(0) {}

Unit::~Unit() {}

bool Unit::Write(size_t orgin, void* buffer, size_t count)
{
	int file_handle = open(name_.c_str(), O_WRONLY);
    lseek(file_handle, orgin, SEEK_SET);
    write(file_handle, buffer, count);
    close(file_handle);
	return true;
}

bool Unit::Read(size_t orgin, void* buffer, size_t count)
{
	int file_handle = open(name_.c_str(), O_RDONLY);
    lseek(file_handle, orgin, SEEK_SET);
    read(file_handle, buffer, count);
    close(file_handle);
	return true;
}

bool Unit::Create()
{
	int file_handle = open(name_.c_str(), O_CREAT | O_WRONLY, 0777);
	close(file_handle);
	return true;
}

bool Unit::Delete()
{
	GSingle(LevelDBManager)->DeleteUnit(id_);
	remove(name_.c_str());
	return true;
}

int Unit::GetId()
{
	return id_;
}

std::string Unit::GetName()
{
	return name_;
}
