#include "data_server.h"
#include "../../common/log4z/log4z.h"

ClientNetwork::HandleMap ClientNetwork::handle_map_;

void ClientNetwork::NetHandle(void* net_pack)
{
	CommonPackage com_pack = static_cast<CommonPackage>(net_pack);
/*
	NetDataHeader* net_header = static_cast<NetDataHeader*>(com_pack->GetData());
	if(net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)
	{
		LogError("ClientNetwork::NetHandle net_header->data_type_ <= NetTypeMin || net_header->data_type >= NetTypeMax)");
		return;
	}
*/
	map_handle_[net_header->data_type](com_pack->GetEvent(), com_pack->GetData());
}

bool ClientNetwork::SendMessage(void* event, void* data, size_t size)
{
	ClientEvent* client_event = static_cast<ClientEvent*>(event);
	client_event->Write(data, size);
	return true;	
}

ClientEvent* ClientNetwork::Connection(const std::string& ip, int32_t port)
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
		LogError("ClientNetwork::Connection status == 0");
		return nullptr;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		LogError("ClientNetwork::Connection -1 == sockfd");
		return nullptr;
	}
	status = connect(sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr));
	if(-1 == status)
	{
		LogError("ClientNetwork::Connection -1 == sockfd");
		return nullptr;
	}

	struct bufferevent* bev = bufferevent_socket_new(getBase(), sockfd, BEV_OPT_CLOSE_ON_FREE);
	ClientEvent* client_event = new ClientEvent();
	if(nullptr == client_event)
	{
		LogError("ClientNetwork::Connection nullptr == client_event");
		return nullptr;
	}
	client_event->SetBuffer(bev);
	client_event->Init();
	return client_event;
}
//注册
void ClientNetwork::RegisterProcess(void)
{
	handle_map_.insert(make_pair(GC_CreateVirtualVolume, ClientNetwork::CGCreateVirtualVolume));
	handle_map_.insert(make_pair(GC_DeleteVirtualVolume, ClientNetwork::CGDeleteVirtualVolume));
	handle_map_.insert(make_pair(GC_UpdateVirtualVolume, ClientNetwork::CGUpdateVirtualVolume));

	handle_map_.insert(make_pair(GC_ReadVirtualVolume, ClientNetwork::GCReadVirtualVolume));

	handle_map_.insert(make_pair(DC_ReadVolume, ClientNetwork::DCReadVolume));
}
//创建卷
bool ClientNetwork::GCCreateVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::GDCreateVolume nullptr == event || nullptr == data");
		return false;
	}
	GC_CreateVirtualVolumemessage* pack = static_cast<GC_CreateVirtualVolumeMessage*>(data);
	if(promise_list_.empty())
	{
		LogError("ClientNetwork::GCCreateVirtualVolume promise_list_.empty()");
		return false;
	}
	std::promise<PromiseInfo>* promise = promise_list_.front();
	promise_list_.pop();
	if(nullptr == promise)
	{
		LogError("ClientNetwork::GCCreateVirtualVolume nullptr == promise");
		return false;
	}
	promise->set_value(&pack->code);
	return true;
}

//删除卷
bool ClientNetwork::GCDeleteVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::GCDeleteVirtualVolume nullptr == event || nullptr == data");
		return false;

	}
    GC_DeleteVirtualVolumeMessage* pack = static_cast<GC_DeleteVirtualVolumeMessage*>(data);
    if(promise_list_.empty())
    {   
        LogError("ClientNetwork::GCDeleteVirtualVolume promise_list_.empty()");
        return false;
    }
    std::promise<PromiseInfo>* promise = promise_list_.front();
    promise_list_.pop();
    if(nullptr == promise)
    {   
        LogError("ClientNetwork::GCDeleteVirtualVolume nullptr == promise");
        return false;
    }
    promise->set_value(&pack->code);
    return true;
}

//写入卷
//暂时先不实现该功能
bool ClientNetwork::GCUpdateVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::GCUpdateVirtualVolume nullptr == event || nullptr == data");
		return false;
	}
	GC_UpdateVirtualVolumeMessage* pack = static_cast<GC_UpdateVirtualVolumeMessage*>(data);
    if(promise_list_.empty())
    {
        LogError("ClientNetwork::GCDeleteVirtualVolume promise_list_.empty()");
        return false;
    }
    std::promise<PromiseInfo>* promise = promise_list_.front();
    promise_list_.pop();
    if(nullptr == promise)
    {
        LogError("ClientNetwork::GCDeleteVirtualVolume nullptr == promise");
        return false;
    }
    promise->set_value(&pack->code);
    return true;
}

//读取卷
bool ClientNetwork::GCReadVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::CDReadVolume nullptr == event || nullptr == data");
		return false;
	}
	GC_ReadVirtualVolumeMessage* pack = static_cast<GC_ReadVirtualVolumeMessage*>(data);
	if(Return_Fail == pack->code_)
	{
		if(promise_list_.empty())
		{
			LogError("ClientNetwork::GCReadVirtualVolume promise_list_.empty()");
			return false;
		}
		std::promise<PromiseInfo>* promise = promise_list_.front();
		promise_list_.pop();
		if(nullptr == promise)
		{
			LogError("ClientNetwork::GCReadVirtualVolume nullptr == promise");
			return false;
		}
		promise->set_value(&pack_code_);
		return false;
	}
	auto it = data_event_map_.find(pack->id_);
	if(data_event_map_.end() != it)
	{
		LogError("ClientNetwork::GCReadVirtualVolume data_event_map_.end() != it");
		return false;
	}
	CD_ReadVolumeMessage msg;
	msg.header_.data_type_ = CD_ReadVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(DataNetHeader);
	strcmp(msg.name, pack->name);
	msg.orgin_ = pack->orgin_;
	msg.size_ = pack->size_;
	SendMessage(static_cast<void*>(it->second), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

bool ClientNetwork::DCReadVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::DCReadVolume nullptr == event || nullptr == data");
		return false;
	}
	DC_ReadVolumeMessage* pack = static_cast<DC_ReadVolumeMessage*>(data);
	if(promise_list_.empty())
	{
		LogError("ClientNetwork::DCReadVolume promise_list_.empty()");
		return false;
	}
	std::promise<PromiseInfo>* promise = promise_list_.front();
	promise_list_.pop();
	if(nullptr == promise)
	{
		LogError("ClientNetwork::DCReadVolume nullptr == promise");
		return false;
	}
	promise->set_value(data);
	return true;
}

ClientNetwork::ClientNetwork():
	MainEvent("127.0.0.1", 8888), CommonThread() {}

ClientNetwork::~ClientNetwork() {}

bool ClientNetwork::CreateFile(const std::string& name)
{
	if(name.empty() || name.size() > MaxVolumeNameSize);
	{
		LogError("ClientNetwork::CreateFile name.empty() || name.size() > MaxVolumeNameSize");
		return false;
	}
	if(nullptr == gate_event_)
	{
		LogError("ClientNetwork::CreateFile nullptr == gate_event_");
		return false;
	}
	std::promise<PromiseInfo> promise;
	std::future<PromiseInfo> futrue = promise.get_future();
	promise_list_.push(&promise);
	CG_CreateVirtualVolume msg;
	strcpy(msg.name_, name.c_str());
	msg.header_.data_type_ = CG_CreateVirtualVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(DataNetHeader);
	SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
	return Return_Fail != *static_cast<uint32_t*>(future.get().data);
}

bool ClientNetwork::DeleteFile(const std::string& name)
{
	if(name.empty() || name.size() > MaxVolumeNameSize);
    {   
        LogError("ClientNetwork::DeleteFile name.empty() || name.size() > MaxVolumeNameSize");
        return false;
    }   
    if(nullptr == gate_event_)
    {   
        LogError("ClientNetwork::DeleteFile nullptr == gate_event_");
        return false;
    }   
    std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> futrue = promise.get_future();
    promise_list_.push(&promise);
    CG_CreateVirtualVolume msg;
    strcpy(msg.name_, name.c_str());
    msg.header_.data_type_ = CG_DeleteVirtualVolume;
    msg.header_.data_size_ = sizeof(msg) - sizeof(DataNetHeader);
    SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
    return Return_Fail != *static_cast<uint32_t*>(future.get().data);
}

bool ClientNetwork::WriteFile(const std::string& name, size_t orgin, void* data, size_t size)
{
	if(name.empty() || name.size() > MaxVolumeNameSize)
	{
		LogError("ClientNetwork::WriteFile name.empty() || name.size() > MaxVolumeNameSize");
		return false;
	}
	if(nullptr == gate_event_)
	{
		LogError("ClientNetwork::WriteFile nullptr == gate_event_");
		return false;
	}
	size_t size = sizeof(CG_UpdateVirtualVolumeMessage) + sizeof(char) * size;
	CG_UpdateVirtualVolumeMessage* msg = static_cast<CG_UpdateVirtualVOlume*>(malloc(size));
	msg->header_.data_type_ = CG_UpdateVirtualVolume;
	msg->header_.data_size_ = size - sizeof(DataNetHeader);
	memcpy(msg->name_, name.c_str(), name.size());
	memcpy(msg->data_, data, size);
	msg->size_ = size;
	msg->orgin_ = orgin_;
	
	std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> futrue = promise.get_future();
    promise_list_.push(&promise);
	
	SendMessage(static_cast<void*>(gate_event_), static_cast<msg>, size);

	return Return_Fail != *static_cast<uint32_t*>(future.get().data);
}

bool ClientNetwork::ReadFile(const std::string& name, size_t orgin, void* data, size_t size)
{
	if(name.empty() || name.size() > define MaxVolumeNameSize)
	{
		LogError("ClientNetwork::ReadFile name.empty() || name.size() > define MaxVolumeNameSize");
		return false;
	}
	if(nullptr == gate_event_)
	{
		LogError("ClientNetwork::ReadFile nullptr == gate_event_");
		return false;
	}
	
	CG_ReadVirtualVolumeMessage msg;
	memcpy(msg.name_, name.c_str, name.size());
	msg.orgin_ = orgin;
	msg.size_ = size;
	
	std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> futrue = promise.get_future();
    promise_list_.push(&promise);

    SendMessage(static_cast<void*>(gate_event_), static_cast<msg>, size);
	
	data = futrue.get().data;
	if(nullptr == data)
	{
		LogError("ClientNetwork::ReadFile nullptr == data");
		return false;
	}
	return true;
}


























