#include "../../common/log4z/log4z.h"
#include "../../common/def/def.h"
#include "client_network.h"
#include <chrono>
#include <thread>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>



using namespace zsummer::log4z;

ClientNetwork* client_network = nullptr;

std::unordered_map<std::string, std::function<void(std::string)> > control_map;

void Init()
{
	ILog4zManager::GetInstance()->Start();
    client_network->Instance();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Upload(const std::string& name)
{
	client_network->CreateFile(name);
	int fd = open(name.c_str(), O_RDONLY);
	if(fd == -1)
	{
		LogError("Upload fd == -1");
		return;
	}
	char buffer[100];
	memset(buffer, 0, sizeof(buffer));
	size_t seek = 0;
	size_t size;
	while((size = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		client_network->WriteFile(name.c_str(), seek, buffer, size);
		seek += size;
		++seek;
	}
}

void Download(const std::string& name)
{
	char buffer[100];
	int fd = open(name.c_str(), O_CREAT | O_WRONLY);
	if(fd == -1) 
    {   
        LogError("Download fd == -1");
        return;
    }   
	
	size_t size = client_network->SizeFile(name);
	std::cerr << "^^^^^^" << size << std::endl;
	size_t seek = 0;
	
	size_t len = size > 100 ? 100 : size;
	int num = static_cast<int>(std::ceil(static_cast<double>(size) / 100));
	for(int i = 1; i <= num; i++)
	{
		len = std::min(100, static_cast<int>(size));
		memset(buffer, 0, sizeof(buffer));
		client_network->ReadFile(name, seek, buffer, len);
		lseek(fd, seek, SEEK_SET);
		write(fd, buffer, len);
		seek += len;
		size -= len;
		len = size > 100 ? 100 : size;
	}
	close(fd);
/*	while(client_network->ReadFile(name, seek, buffer, 100))
	{
		lseek(fd, seek, SEEK_SET);
		write(fd, buffer, 100);
		seek += 100;
		seek += 1;
	}
*/
}

void Delete(const std::string& name)
{
	client_network->DeleteFile(name);
}

void Create(const std::string& name)
{
	client_network->CreateFile(name);
} 

void Register()
{
	control_map.insert(std::make_pair("CreateFile", Create));
	control_map.insert(std::make_pair("DeleteFile", Delete));
	control_map.insert(std::make_pair("UploadFile", Upload));
	control_map.insert(std::make_pair("DownloadFile", Download));
}

int main(int argc, char**argv)
{
	client_network = new ClientNetwork(argv[1], argv[2]);
	Init();
	Register();

	std::string control;
	std::string name;
	while(std::cin >> control >> name)
	{
		control_map[control](name);
	}

	client_network->Join();
}

















