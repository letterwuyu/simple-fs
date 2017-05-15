#include "data_server.h"
#include "../../common/log4z/log4z.h"

DataServer::HandleMap DataServer::handle_map_;

void DataServer::NetHandle(void* net_pack)
{
	CommonPackage com_pack = static_cast<CommonPackage>(net_pack)
	NetDataHeader* net_header = static_cast<NetDataHeader*>(com_pack->GetData());
	if(net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)
	{
		LogError("DataServer::NetHandle net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)");
		return;
	}
	map_handle_[net_header->data_type](com_pack->GetEvent(), com_pack->GetEvent());
}

DataEvent* DataServer::Connection(const std::string& ip, int32_t port)
{
	int sockfd, status, save_errno;
	struct sockaddr_in server_addr;
	memset(scokaddr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	status = inet_aton(ip.c_str(), &server_addr.sin_addr);
	if(!status)
	{
		LogError("DataServer::Connection status == 0");
		return nullptr;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		LogError("DataServer::Connection -1 == sockfd");
		return nullptr;
	}
	status = connect(sockfd, static_cast<struct sockaddr*>(&server_addr), sizeof(server_addr));
	if(-1 == status)
	{
		LogError("DataServer::Connection -1 == sockfd");
		return nullptr;
	}
	
	struct bufferevent* bev = bufferevent_socket_new(_base, sockfd, BEV_OPT_CLOSE_ON_FREE);
	struct event* ev_cmd = event_new(base, STDIN_FILENO,  
                                      EV_READ | EV_PERSIST, cmd_msg_cb,  
                                      static_cast<void*>(bev));
	event_add(ev_cmd, NULL);
	DataEvent* data_event = new DataEvent();
	if(nullptr == data_event)
	{
		LogError("DataServer::Connection nullptr == data_event");
		return nullptr;
	}
	data_event->SetBuffer(bev);
	data_event->Init();
	return data_event;
}

DataServer::DataServer():
	MainEvent("127.0.0.1", 8888), CommonThread() {}

DataServer::~DataServer() {}

