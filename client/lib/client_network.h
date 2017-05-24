#ifndef _CLIENT_NETWORK_H__
#define _CLIENT_NETWORK_H__

#include "../../common/net/libevent_network.h"
#include "../../common/imp/common_thread.h"
#include "data_event.h"

#include <funtional>
#include <vector>
#include <map>

using namespace net;

class ClientNetwork:public EventMain, public CommonThread {
public:
	ClientNetwork();
	~ClientNetwork();
public:
	typedef std::funtion<bool(void*, void*)> HandleType;
	typedef std::unordered_map<int32_t, HandleType> HandleMap;
	void ListenHandle(struct bufferevent *bev);
	void Run(void);
public:
	static void NetHandle(void* net_pack);
private:
	static bool SendMessage(void* event, void* data, size_t size);
	static ClientEvent* Connection(const std::string& ip, int32_t port);
	static void RegisterProcess(void);

	static bool GCCreateVritualVolume(void* event, void* data);
	static bool GCDeleteVirtualVolume(void* event, void* data);
	static bool GCUpdateVirtualVolume(void* event, void* data);
	
	static bool GCReadVirtualVolume(void* event, void* data);
	
	static bool DCReadVolume(void* event, void* data);
public:
	void CreateFile(const std::string& name);
	void DeleteFile(const std::string& name);
	void WriteFile(const std::string& name, size_t orgin, void* data, size_t size);
	void ReadFile(const std::string& name, size_t orgin, void* data, size_t size);
private:
	static HandleMap handle_map_;
	std::vector<ClientEvent*> events_;
	ClientEvent* GateLink;
};

#endif //_CLIENT_NETWORK_H__
