#ifndef _CLIENT_NETWORK_H__
#define _CLIENT_NETWORK_H__

#include "../../common/net/libevent_network.h"
//#include "../../common/imp/common_thread.h"
#include "../../common/imp/cxx_thread.h"
#include "client_event.h"
#include "promise_info.h"

#include <unordered_map>
#include <functional>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include <queue>
#include <list>

using namespace net;

class ClientNetwork:public MainEvent, public CxxThread {
public:
	ClientNetwork();
	~ClientNetwork();
	void Instance();
public:
	typedef std::function<bool(void*, void*)>        	HandleType;
	typedef std::unordered_map<int32_t, HandleType> 	HandleMap;
	typedef std::queue<std::promise<PromiseInfo>* > 	PromiseList;
	typedef std::unordered_map<int, ClientEvent*>            DataEventMap;

	void ListenHandle(struct bufferevent *bev, struct sockaddr *sa, int socklen);
	void Run(void);
public:
	static void NetHandle(void* net_pack);
private:
	static bool SendMessage(void* event, void* data, size_t size);
	ClientEvent* Connection(const std::string& ip, int32_t port);
	static void RegisterProcess(void);

	static bool GCCreateVirtualVolume(void* event, void* data);
	static bool GCDeleteVirtualVolume(void* event, void* data);
	static bool GCUpdateVirtualVolume(void* event, void* data);
	
	static bool GCReadVirtualVolume(void* event, void* data);
	
	static bool DCReadVolume(void* event, void* data);
public:
	bool CreateFile(const std::string& name);
	bool DeleteFile(const std::string& name);
	bool WriteFile(const std::string& name, size_t orgin, void* data, size_t size);
	bool ReadFile(const std::string& name, size_t orgin, void* data, size_t size);
private:
	static HandleMap handle_map_;
	static PromiseList promise_list_;
	static ClientEvent* gate_event_;
	static DataEventMap data_event_map_;

	std::vector<ClientEvent*> events_;
};

#endif //_CLIENT_NETWORK_H__
