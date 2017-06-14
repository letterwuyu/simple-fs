#ifndef _TRABSFER_H_
#define _TRANSFER_H_

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

enum FileOperator
{
	OnlyRead  = O_RDONLY,
	OnlyWrite = O_WRONLY,
	Create    = O_CREAY,    
};

static int Create(const std::string& name)
{
	return create(name.c_str());
}

static int Open(const std::string& name)
{
	return open(name.c_str());
}

static int Open(int file_handle)
{
	return open(file_handle);
}

static int Close(int file_handle)
{
	return close(file_handle);
}

static int Read(int file_handle, void** buffer, size_t nbytes)
{
	read(file_handle, *buffer, nbytes);
}

static int Write(int file_handle, const void** buffer, size_t nbytes)
{
	write(file_handle, *buffer, nbytes);
}
#endif /* _TRANSFER_H_ */








