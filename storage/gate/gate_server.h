#ifndef _GATE_SERVER_H__
#define _GATE_SERVER_H__

#include "../../common/net/libevent_network.h"
#include "../../common/imp/common_thread.h"
#include "data_event.h"

#include <funtional>
#include <vector>
#include <map>

using namespace net;

class GateServer:public EventMain, public CommonThread {
public:
	GateServer();
	~GateServer();
public:
	typedef std::funtion<bool(void*, void*)> HandleType;
	typedef std::unordered_map<int32_t, HandleType> HandleMap;
	void ListenHandle(struct bufferevent *bev);
	void Run(void);
public:
	static void NetHandle(void* net_pack);
private:
	static bool SendMessage(void* event, void* data, size_t size);
	static GateEvent* Connection(const std::string& ip, int32_t port);
	static void RegisterProcess(void);

	static bool CGCreateVirtualVolume(void* event, void* data);
	static bool CGDeleteVirtualVolume(void* event, void* data);
	static bool CGUpdateVirtualVolume(void* event, void* data);
	
	static bool CGReadVolume(void* event, void* data);	
private:
	static HandleMap handle_map_;
	std::vector<GateEvent*> events_;
};

#endif //_GATE_SERVER_H__
#endif //_GATE_SERVER_H__

