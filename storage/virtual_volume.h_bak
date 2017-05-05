#ifndef VIRTUAL_VOLUME_H
#define VIRTUAL_VOLUME_H
#include <map>
#include <vector>
#include <random>
#include "volume.h"
#include "session.h"
#include "../common/def.def.h"
#include "../common/net/libevent_socket.h"

using namespace net;

class VirtualVolume {
public:
	VirtualVolume(uint64 volume_id):volume_id_(volume_id) {}
	void AddStorage(SocketEvent* storage)
	{
		storages_.push_back(storage);
	}
	void DeleteStorage(SockEvent* storage)
	{
		for(auto it = storages_.begin(); it != storages_.end(); ++it)
		{
			if(*it == storage)
			{
				it = storages_.erase(it);
			}
		}
	}
	vector<SocketEvent*>& GetList()
	{
		return storages_;
	}
	
	SocketEvent* SelectStorage()
	{
		if(storages_.empty())
			return NULL;
		std::default_random_engine random;
		std::uniform_int_distribution<int> dis(0, storages_.size());
		return storages_[dis(random)];
	}
	uint64 GetVolumeId()
	{
		return volume_id_;
	}
private:
	vector<SocketEvent*> storages_;
	uint64 volume_id_;
};
#endif /* VIRTUAL_VOLUME_H */
