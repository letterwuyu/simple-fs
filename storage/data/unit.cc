#include "unit.h"

Unit::Unit(const std::string& name, uint64 id): name_(name), id_(id), size_(0) {}

Unit::~Unit() {}

bool Unit::Write(size_t orign, void* buffer, size_t count)
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
	remove(name_.c_str());
	return true;
}
uint64 Unit::GetId()
{
	return id_;
}

string Unit::GetName()
{
	return name_;
}
