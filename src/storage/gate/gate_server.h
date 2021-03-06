#ifndef _GATE_SERVER_H__
#define _GATE_SERVER_H__

#include "../../common/net/libevent_network.h"
#include "../../common/imp/common_thread.h"
#include "gate_event.h"

#include <functional>
#include <vector>
#include <map>
#include <unordered_map>

using namespace net;
//using namespace imp;

class GateServer:public MainEvent, public CommonThread {
public:
	GateServer();
	~GateServer();
public:
	typedef std::function<bool(void*, void*)> HandleType;
	typedef std::unordered_map<int, HandleType> HandleMap;
	void ListenHandle(struct bufferevent *bev, struct sockaddr *sa, int socklen);
	void Run(void);
public:
	static void NetHandle(void* net_pack);
private:
	static bool SendMessage(void* event, void* data, size_t size);
	GateEvent* Connection(const std::string& ip, int32_t port);
	static void RegisterProcess(void);

	static bool CGCreateVirtualVolume(void* event, void* data);
	static bool CGDeleteVirtualVolume(void* event, void* data);
	static bool CGUpdateVirtualVolume(void* event, void* data);
	static bool CGReadVirtualVolume(void* event, void* data);
	static bool CGReadVolume(void* event, void* data);
	static bool CGVirtualVolumeSize(void* event, void* data);

	static bool DGShake(void* event, void* data);
	static bool DGCreateVolume(void* event, void* data);
	static bool DGDeleteVolume(void* event, void* data);
	static bool DGUpdateVolume(void* event, void* data);
private:
	static HandleMap handle_map_;
	std::vector<GateEvent*> events_;
};

#endif //_GATE_SERVER_H__
