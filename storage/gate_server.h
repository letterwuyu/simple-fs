#ifndef GATE_SERVER_H
#define GATE_SERVER_H
#include "global.h"

class GateSocket:public SocketEvent {
public:
	GateSocket();
	void ReadHandle(struct bufferevent* bev);
private:
	bool TcpDataSplit(const char* recv_data, size_t recv_size);
	void HandleNetPack(NetDataHeader* header);
	char last_save_data_[kMaxNetPackSize];
    size_t remain_size_;
    bool first_;
};

class GateServer:public MainEvent, public commonThread {
public:
	void ListenHandle(struct bufferevent *bev);
	void Run();
private:
	vector<shared_ptr<GateSocket>> sockets_;
};

#endif //GATE_SERVER_H
