#ifndef _DATA_SERVER_H__
#define _DATA_SERVER_H__

#include "../../common/net/libevent_network.h"
#include "../../common/imp/common_thread.h"
#include "data_event.h"

#include <functional>
#include <vector>
#include <map>
#include <unordered_map>

using namespace net;

class DataServer: public MainEvent, public CommonThread {
public:
	DataServer();
	~DataServer();
public:
	typedef std::function<bool(void*, void*)> HandleType;
	typedef std::unordered_map<int, HandleType> HandleMap;
	void ListenHandle(struct bufferevent *bev, struct sockaddr *sa, int socklen);
	void Run(void);
public:
	void ShakeGate(void);
public:
	static void NetHandle(void* net_pack);
private:
	static bool SendMessage(void* event, void* data, size_t size);
	DataEvent* Connection(const std::string& ip, int32_t port);
	static void RegisterProcess(void);

	static bool GDCreateVolume(void* event, void* data);
	static bool GDDeleteVolume(void* event, void* data);
	static bool GDUpdateVolume(void* event, void* data);
	
	static bool CDReadVolume(void* event, void* data);	
	static bool CDVolumeSize(void* event, void* data);
private:
	static HandleMap handle_map_;
	std::vector<DataEvent*> events_;
	DataEvent* gate_link;
};

#endif //_DATA_SERVER_H__
