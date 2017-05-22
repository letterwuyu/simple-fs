#ifndef _DATA_SERVER_H__
#define _DATA_SERVER_H__

#include "../../common/net/libevent_network.h"
#include "../../common/imp/common_thread.h"
#include "data_event.h"

#include <funtional>
#include <vector>
#include <map>

using namespace net;

class DataServer:public EventMain, public CommonThread {
public:
	DataServer();
	~DataServer();
public:
	typedef std::funtion<bool(void*, void*)> HandleType;
	typedef std::unordered_map<int32_t, HandleType> HandleMap;
	void ListenHandle(struct bufferevent *bev);
	void Run(void);
public:
	static void NetHandle(void* net_pack);
private:
	static bool SendMessage(void* event, void* data, size_t size);
	static DataEvent* Connection(const std::string& ip, int32_t port);
	static void RegisterProcess(void);

	static bool GDCreateVolume(void* event, void* data);
	static bool GDDeleteVolume(void* event, void* data);
	static bool GDUpdateVolume(void* event, void* data);
	
	static bool CDReadVolume(void* event, void* data);	
private:
	static HandleMap handle_map_;
	std::vector<DataEvent*> events_;
	DataEvent* GateLink;
};

#endif //_DATA_SERVER_H__
