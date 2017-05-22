#include "gate_server.h"
#include "../../common/log4z/log4z.h"

GateServer::HandleMap GateServer::handle_map_;

void GateServer::NetHandle(void* net_pack)
{
	CommonPackage com_pack = static_cast<CommonPackage>(net_pack);
/*
	NetGateHeader* net_header = static_cast<NetGateHeader*>(com_pack->GetGate());
	if(net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)
	{
		LogError("GateServer::NetHandle net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)");
		return;
	}
*/
	map_handle_[net_header->data_type](com_pack->GetEvent(), com_pack->GetGate());
}

bool GateServer::SendMessage(void* event, void* data, size_t size)
{
	GateEvent* data_event = static_cast<GateEvent*>(event);
	data_event->Write(data, size);
	return true;	
}

GateEvent* GateServer::Connection(const std::string& ip, int32_t port)
{
	evutil_socket_t sockfd;
	int status, save_errno;
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
	GateEvent* gate_event = new GateEvent();
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
	handle_map_.insert(make_pair(CG_CreateVirtualVolume, GateServer::CGCreateVirtualVolume));
	handle_map_.insert(make_pair(CG_DeleteVirtualVolume, GateServer::CGDeleteVirtualVolume));
	handle_map_.insert(make_pair(CG_UpdateVirtualVolume, GateServer::CGUpdateVirtualVolume));

	handle_map_.insert(make_pair(CG_ReadVirtualVolume, GateServer::CGReadVirtualVolume));
}
//创建卷
bool GateServer::CGCreateVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::GDCreateVolume nullptr == event || nullptr == data");
		return false;
	}
	CG_CreateVolumeMessage* pack = static_cast<GD_CreateVolumeMessage*>(data);
	char volume_name[MaxVolumeNameSize];
	memcpy(volume_name, pack->name_, MaxVolumeNameSize);
	//数据最后一位赋值‘\0’ 防止内存越界
	volume_name[MaxVolumeNameSize - 1] = '\0';
	//创建volume
	Volume* volume = GSingle(VolumeManager).CreateVolume(std::string(volume));
	DG_CreateVolumeMessage msg;
	if(nullptr == volume)
	{
		LogError("GateServer::GDCreateVolume nullptr == volume");
		msg.code_ = Return_Fail;
	}
	else
	{
		msg.code_ = Return_Succeed;
	}
	msg.header.data_type_ = DG_CreateVolume;
	msg.header.data_size_ = sizeof(msg) - sizeof(GateNetHeader);
	SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

//删除卷
bool GateServer::GDDeleteVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::DG_DeleteVolume nullptr == event || nullptr == data");
		return false;
	}
	GD_DeleteVolumeMessage* pack = static_cast<DG_DeleteVolumeMessage*>(data);
	char volume_name[MaxVolumeNameSize];
    memcpy(volume_name, pack->name_, MaxVolumeNameSize);
    //数据最后一位赋值‘\0’ 防止内存越界
    volume_name[MaxVolumeNameSize] = '\0';
	DG_DeleteVolumeMessage msg;
	msg.header_.data_type_ = DG_DeleteVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(GateNetheader);
	if(GSingle(VolumeManager).DeleteVolume(std::string(volume_name)))
	{
		msg.code_ = Return_Succeed;
	}
	else
	{
		msg.code_ = Return_fail;
	}
	SendMssage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

//写入卷
//暂时先不实现该功能
bool GateServer::GDUpdateVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::DGUpdateVolume nullptr == event || nullptr == data");
		return false;
	}
	DG_UpdateVolumeMessage msg;
	msg.header_.data_type_ = DG_UpdateVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(GateNetHeader);
	msg.code_ = Return_Succeed;
	SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

//读取卷
bool GateServer::CDReadVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("GateServer::CDReadVolume nullptr == event || nullptr == data");
		return false;
	}
	
	CD_ReadVolumeMessage* pack = static_cast<CD_ReadVolumeMessage*>(data);
	pack->name_[MaxVolumeNameSize - 1] = '/0';
	Volume* volume = GSingle(VolumeManager).GetVolume(std::string(pack->name_));
	if(nullptr == volume)
	{
		LogError("GateServer::CDReadVolume nullptr == volume");
		DC_ReadVolume msg;
		msg.header_.data_type_ = DC_ReadVolume;
		msg.header_.data_size_ = sizeof(msg) - sizeof(GateNetHeader);
		strcmp(msg.name_, pack->name_);
		msg.code_ = Return_Fail;
		SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
		return false; 
	}
	else
	{
		size_t size = sizeof(msg) + pack->size_ * sizeof(char);
		DC_ReadVolume* msg = static_cast<DC_ReadVolume*>(malloc(size));
		msg->header_.data_type_ = DC_ReadVolume;
		msg->header_.data_size_ = size = sizeof(GateNetHeader);
		strcmp(msg->name_, pack->name_);
		volume->Read(pack->orgin_, msg->data_, pack->size_);
		msg->size_ = pack->size_;
		msg->orgin_ = pack->orgin_;
		SendMessage(static_cast<void*>(event), static_cast<void*>(msg), size);
		return true;
	}
}

GateServer::GateServer():
	MainEvent("127.0.0.1", 8888), CommonThread() {}

GateServer::~GateServer() {}

