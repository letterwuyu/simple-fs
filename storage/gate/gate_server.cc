#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "gate_server.h"
#include "../../common/imp/singleton.h"
#include "../../common/log4z/log4z.h"
#include "../../common/def/def.h"
//#include "../../common/def/gc_net_def.h"
#include "../../common/def/gc_net_struct.h"
#include "../../common/def/cg_net_struct.h"
//#include "../../common/def/gd_net_def.h"
#include "../../common/def/gd_net_struct.h"
#include "../../common/def/dg_net_struct.h"
#include "../../common/def/def_enum.h"
#include "../../common/net/common_package.h"
#include "../../common/net/package_analysis.h"
#include "virtual_volume.h"
#include "virtual_volume_manager.h"
using namespace imp;

GateServer::HandleMap GateServer::handle_map_;

void GateServer::NetHandle(void* net_pack)
{
	CommonPackage* com_pack = static_cast<CommonPackage*>(net_pack);
/*
	NetGateHeader* net_header = static_cast<NetGateHeader*>(com_pack->GetGate());
	if(net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)
	{
		LogError("GateServer::NetHandle net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)");
		return;
	}
*/
	handle_map_[static_cast<NetDataHeader*>(com_pack->GetData())->data_type_](com_pack->GetEvent(), com_pack->GetData());
}

bool GateServer::SendMessage(void* event, void* data, size_t size)
{
	GateEvent* gate_event = static_cast<GateEvent*>(event);
	gate_event->Write(data, size);
	return true;	
}

GateEvent* GateServer::Connection(const std::string& ip, int32_t port)
{
	evutil_socket_t sockfd;
	int status;
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	status = inet_aton(ip.c_str(), &server_addr.sin_addr);
	if(!status)
	{
		LogError("GateServer::Connection status == 0");
		return nullptr;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		LogError("GateServer::Connection -1 == sockfd");
		return nullptr;
	}
	status = connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr));
	if(-1 == status)
	{
		LogError("GateServer::Connection -1 == sockfd");
		return nullptr;
	}

	struct bufferevent* bev = bufferevent_socket_new(getBase(), sockfd, BEV_OPT_CLOSE_ON_FREE);
	GateEvent* gate_event = new GateEvent(NetHandle);
	if(nullptr == gate_event)
	{
		LogError("GateServer::Connection nullptr == data_event");
		return nullptr;
	}
	gate_event->SetBuffer(bev);
	gate_event->Init();
	return gate_event;
}
//注册
void GateServer::RegisterProcess(void)
{
	handle_map_.insert(std::make_pair(CG_CreateVirtualVolume, GateServer::CGCreateVirtualVolume));
	handle_map_.insert(std::make_pair(CG_DeleteVirtualVolume, GateServer::CGDeleteVirtualVolume));
	handle_map_.insert(std::make_pair(CG_UpdateVirtualVolume, GateServer::CGUpdateVirtualVolume));

	handle_map_.insert(std::make_pair(CG_ReadVirtualVolume, GateServer::CGReadVirtualVolume));

	handle_map_.insert(std::make_pair(DG_Shake, GateServer::DGShake));
}

//创建卷
bool GateServer::CGCreateVirtualVolume(void* event, void* data)
{
	std::cerr << "create virtual volume" << std::endl;
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::GDCreateVolume nullptr == event || nullptr == data");
		return false;
	}
	CG_CreateVirtualVolumeMessage* pack = static_cast<CG_CreateVirtualVolumeMessage*>(data);
	char virtual_volume_name[MaxVolumeNameSize];
	memcpy(virtual_volume_name, pack->name_, MaxVolumeNameSize);
	//数据最后一位赋值‘\0’ 防止内存越界
	virtual_volume_name[MaxVolumeNameSize - 1] = '\0';
	//创建virtualvolume
	VirtualVolume* virtual_volume = GSingle(VirtualVolumeManager)->CreateVirtualVolume(std::string(virtual_volume_name));
	if(nullptr == virtual_volume)
	{
		LogError("GateServer::CGCreateVirtualVolume nullptr == virtual_volume");
		GC_CreateVirtualVolumeMessage msg;
		msg.header_.data_type_ = GC_CreateVirtualVolume;
		msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
		msg.code_ = Return_Fail;
		SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
		return false;
	}
	else
	{
		{
			GD_CreateVolumeMessage msg;
			msg.header_.data_type_ = GD_CreateVolume;
			msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
			memcpy(msg.name_, virtual_volume_name, MaxVolumeNameSize);
			VirtualVolume::ServerList server_list = virtual_volume->GetServerList();
			for(auto it = server_list.begin(); it != server_list.end(); ++it)
			{
				(*it)->socket_event_->Write(static_cast<void*>(&msg), sizeof(msg));
			}
		}
		
		{
			GC_CreateVirtualVolumeMessage msg;
        	msg.header_.data_type_ = GC_CreateVirtualVolume;
        	msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
        	msg.code_ = Return_Succeed;
        	SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));	
			return true;
		}
	}
}

//删除卷
bool GateServer::CGDeleteVirtualVolume(void* event, void* data)
{
	//暂不实现
	return true;
}


//写入卷
//暂时先不实现该功能
bool GateServer::CGUpdateVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::DGUpdateVolume nullptr == event || nullptr == data");
		return false;
	}
	return true;
}

//读取卷
bool GateServer::CGReadVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::CGReadVolume nullptr == event || nullptr == data");
		return false;
	}
	CG_ReadVirtualVolumeMessage* pack = static_cast<CG_ReadVirtualVolumeMessage*>(data);
	const VirtualVolume* virtual_volume = GSingle(VirtualVolumeManager)->GetVirtualVolume(std::string(pack->name_));
	if(nullptr == virtual_volume)
	{
		GC_ReadVirtualVolumeMessage msg;
		msg.header_.data_type_ = CG_ReadVirtualVolume;
		msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
		msg.code_ = Return_Fail;
		SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
		return false;
	}
	else
	{
		VirtualVolume::ServerList server_list = virtual_volume->GetServerList();
		GC_ReadVirtualVolumeMessage msg;
		msg.header_.data_type_ = GC_ReadVirtualVolume;
		msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
		msg.code_ = Return_Succeed;
		msg.id_ = (*server_list.begin())->server_id_;
		strcpy(msg.name_, pack->name_);
		msg.orgin_ = pack->orgin_;
		msg.size_ = pack->size_;
		SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
		return true;
	}
}

bool GateServer::DGShake(void* event, void* data)
{
	LogInfo("GateServer::DGShake");
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::DGShake");
		return false;
	}
	DG_ShakeMessage* pack = static_cast<DG_ShakeMessage*>(data);
	ServerInfo server_info;
	server_info.socket_event_ = static_cast<GateEvent*>(event);
	server_info.server_id_ = pack->id_;
	GSingle(ServerManager)->AddServer(server_info);
	return true;
}

GateServer::GateServer():
	MainEvent("127.0.0.1", 8888), CommonThread() {}

GateServer::~GateServer() {}

void GateServer::ListenHandle(struct bufferevent* bev)
{
	GateEvent* gate_event = new GateEvent(NetHandle);
	if(nullptr == gate_event)
	{
		LogError("GateServer::ListenHandle nullptr == gate_event");
		return;
	}
	events_.push_back(gate_event);
}

void GateServer::Run(void)
{
	Init();
	Loop();
}













