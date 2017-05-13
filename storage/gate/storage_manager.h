#ifndef STORAFE_MANAGER
#define STORAGE_MANAGER
#include <vector>
#include <random>
#include "../common/net/libevent_socket.h"

struct StorageInfo
{
	SocketEvent* socket_event_;
};

class StorageManager {
public:
	StorageManager() = default;
	void AddInfo(StorageInfo& info)
	{
		infos.push_back(info);
	}
	void DeleteInfo(StorageInfo& info)
	{
		for(auto it = infos_.begin(); it != infos_.end(); ++it)
		{
			if(*it == info)
			{
				it = infos_.erase(it);
			}
		}
	}
	std::vector<StorageInfo>& GetInfos()
	{
		return infos_;
	}
	SocketEvent* SelectServer()
	{
		if(infos.empty())
			return NULL;
		std::default_random_engin random;
		std::uniform_int_distribution<int> dis(0, infos_.size());
		return infos_[dis(random)].socket_event_;
	}
	size_t ServerNum()
	{
		infos_.size();
	}
private:
	std::vector<StorageInfo> infos_;
};

#endif //STORAGE_MANAGER

