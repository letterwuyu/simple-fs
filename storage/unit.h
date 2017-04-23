#ifndef _UNIT_H_
#define _UNIT_H_
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

class Unit {
public:
	static const size_t Size = 1024 * 1024 * 4;
public:
	Unit(const std::string& name)     : name_(name), size_(0) {}
	Unit(std::string&& name) noexcept : name_(name), size_(0) {}
	virtual ~Unit() {}
public:
	void Write(size_t orign, void* buffer, size_t count)
	{
		int file_handle = open(name_, O_WRONLY);
		lseek(file_handle, orgin, SEEK_SET);
		write(file_handle, buffer, count);
		close(file_handle);
	}
	void Read (size_t orgin, void* buffer, size_t count)
	{
		int file_handle = open(name_, O_RDONLY);
		lseek(file_handle, orgin, SEEK_SET);
		read(file_handle, buffer, count);
		close(file_handle);
	}
private:
	std::string name_;
	size_t      size_;
};

#endif /* _UNIT_H_ */
