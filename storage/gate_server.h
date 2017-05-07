#ifndef GATE_SERVER_H
#define GATE_SERVER_H
#include "global.h"

class GateSocket:public SocketEvent {
public:
	GateSocket();
	void ReadHandle(struct bufferevent* bev);
	typedef std::unordered_map<uint32, function<bool(void*, void*)> > HandleMap;
public:
	static bool InitHandleMap();

	StaticHandle(DG_HandShake);
	StaticHandle(CG_CreateVirtualVolume);
	StaticHandle(CG_LoadVirtualVolume);
	StaticHandle(CG_UpdateVirtualVolume);	
	
private:
	PackageAnalysis package_analysis_;
	static void HandleNetPack(void* header);
	static HandleMap handle_map_;	
};

class GateServer:public MainEvent, public commonThread {
public:
	void ListenHandle(struct bufferevent *bev);
	void Run();
private:
	vector<shared_ptr<GateSocket>> sockets_;
};

#endif //GATE_SERVER_H
