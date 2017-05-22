#include "data_server.h"
#include "../../common/log4z/log4z.h"

DataServer::HandleMap DataServer::handle_map_;

void DataServer::NetHandle(void* net_pack)
{
	CommonPackage com_pack = static_cast<CommonPackage>(net_pack);
/*
	NetDataHeader* net_header = static_cast<NetDataHeader*>(com_pack->GetData());
	if(net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)
	{
		LogError("DataServer::NetHandle net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)");
		return;
	}
*/
	map_handle_[net_header->data_type](com_pack->GetEvent(), com_pack->GetData());
}

bool DataServer::SendMessage(void* event, void* data, size_t size)
{
	DataEvent* data_event = static_cast<DataEvent*>(event);
	data_event->Write(data, size);
	return true;	
}

DataEvent* DataServer::Connection(const std::string& ip, int32_t port)
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
		LogError("DataServer::Connection status == 0");
		return nullptr;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		LogError("DataServer::Connection -1 == sockfd");
		return nullptr;
	}
	status = connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr));
	if(-1 == status)
	{
		LogError("DataServer::Connection -1 == sockfd");
		return nullptr;
	}

	struct bufferevent* bev = bufferevent_socket_new(getBase(), sockfd, BEV_OPT_CLOSE_ON_FREE);
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
//注册
void DataServer::RegisterProcess(void)
{
	handle_map_.insert(make_pair(GD_CreateVolume, DataServer::GDCreateVolume));
	handle_map_.insert(make_pair(GD_DeleteVolume, DataServer::GDDeleteVolume));
	handle_map_.insert(make_pair(GD_UpdateVolume, DataServer::GDUpdateVolume));

	handle_map_.insert(make_pair(CD_ReadVolume, DataServer::CDReadVolume));
}
//创建卷
bool DataServer::GDCreateVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("DataServer::GDCreateVolume nullptr == event || nullptr == data");
		return false;
	}
	GD_CreateVolumeMessage* pack = static_cast<GD_CreateVolumeMessage*>(data);
	char volume_name[MaxVolumeNameSize];
	memcpy(volume_name, pack->name_, MaxVolumeNameSize);
	//数据最后一位赋值‘\0’ 防止内存越界
	volume_name[MaxVolumeNameSize - 1] = '\0';
	//创建volume
	Volume* volume = GSingle(VolumeManager).CreateVolume(std::string(volume));
	DG_CreateVolumeMessage msg;
	if(nullptr == volume)
	{
		LogError("DataServer::GDCreateVolume nullptr == volume");
		msg.code_ = Return_Fail;
	}
	else
	{
		msg.code_ = Return_Succeed;
	}
	msg.header.data_type_ = DG_CreateVolume;
	msg.header.data_size_ = sizeof(msg) - sizeof(DataNetHeader);
	SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

//删除卷
bool DataServer::GDDeleteVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("DataServer::DG_DeleteVolume nullptr == event || nullptr == data");
		return false;
	}
	GD_DeleteVolumeMessage* pack = static_cast<DG_DeleteVolumeMessage*>(data);
	char volume_name[MaxVolumeNameSize];
    memcpy(volume_name, pack->name_, MaxVolumeNameSize);
    //数据最后一位赋值‘\0’ 防止内存越界
    volume_name[MaxVolumeNameSize] = '\0';
	DG_DeleteVolumeMessage msg;
	msg.header_.data_type_ = DG_DeleteVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(DataNetheader);
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
bool DataServer::GDUpdateVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("DataServer::DGUpdateVolume nullptr == event || nullptr == data");
		return false;
	}
	DG_UpdateVolumeMessage msg;
	msg.header_.data_type_ = DG_UpdateVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(DataNetHeader);
	msg.code_ = Return_Succeed;
	SendMessage(static_cast<void*>(event), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

//读取卷
bool DataServer::CDReadVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("DataServer::CDReadVolume nullptr == event || nullptr == data");
		return false;
	}
	
	CD_ReadVolumeMessage* pack = static_cast<CD_ReadVolumeMessage*>(data);
	pack->name_[MaxVolumeNameSize - 1] = '/0';
	Volume* volume = GSingle(VolumeManager).GetVolume(std::string(pack->name_));
	if(nullptr == volume)
	{
		LogError("DataServer::CDReadVolume nullptr == volume");
		DC_ReadVolume msg;
		msg.header_.data_type_ = DC_ReadVolume;
		msg.header_.data_size_ = sizeof(msg) - sizeof(DataNetHeader);
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
		msg->header_.data_size_ = size = sizeof(DataNetHeader);
		strcmp(msg->name_, pack->name_);
		volume->Read(pack->orgin_, msg->data_, pack->size_);
		msg->size_ = pack->size_;
		msg->orgin_ = pack->orgin_;
		SendMessage(static_cast<void*>(event), static_cast<void*>(msg), size);
		return true;
	}
}

DataServer::DataServer():
	MainEvent("127.0.0.1", 8888), CommonThread() {}

DataServer::~DataServer() {}
