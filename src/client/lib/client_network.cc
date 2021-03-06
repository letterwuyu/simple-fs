#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cmath>

#include "client_network.h"
#include "../../common/log4z/log4z.h"
#include "../../common/def/def.h"
#include "../../common/def/def_enum.h"
#include "../../common/net/package_analysis.h"
#include "../../common/net/common_package.h"
#include "../../common/def/gc_net_struct.h"
#include "../../common/def/cg_net_struct.h"
#include "../../common/def/dc_net_struct.h"
#include "../../common/def/cd_net_struct.h"

ClientNetwork::HandleMap ClientNetwork::handle_map_;
ClientNetwork::PromiseList ClientNetwork::promise_list_;
ClientNetwork::DataEventMap ClientNetwork::data_event_map_;
ClientEvent* ClientNetwork::gate_event_;

void ClientNetwork::NetHandle(void* net_pack)
{
	CommonPackage* com_pack = static_cast<CommonPackage*>(net_pack);
	auto it = handle_map_.find(static_cast<NetDataHeader*>(com_pack->GetData())->data_type_);
    if(handle_map_.end() == it) 
    {   
        LogError("DataServer::NetHandle handle_map_.end() == it");
        return;
    }   
    it->second(com_pack->GetEvent(), com_pack->GetData());
}

bool ClientNetwork::SendMessage(void* event, void* data, size_t size)
{
	ClientEvent* client_event = static_cast<ClientEvent*>(event);
	std::cerr << "ClientNetwork::SendMessage" << std::endl;
	client_event->Write(data, size);
	return true;	
}

ClientEvent* ClientNetwork::Connection(const std::string& ip, int32_t port)
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

	struct bufferevent* bev = bufferevent_socket_new(GetGlobalEventBase(), sockfd, BEV_OPT_CLOSE_ON_FREE);
	ClientEvent* client_event = new ClientEvent(NetHandle);
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
	handle_map_.insert(std::make_pair(GC_CreateVirtualVolume, ClientNetwork::GCCreateVirtualVolume));
	handle_map_.insert(std::make_pair(GC_DeleteVirtualVolume, ClientNetwork::GCDeleteVirtualVolume));
	handle_map_.insert(std::make_pair(GC_UpdateVirtualVolume, ClientNetwork::GCUpdateVirtualVolume));

	handle_map_.insert(std::make_pair(GC_ReadVirtualVolume, ClientNetwork::GCReadVirtualVolume));
	handle_map_.insert(std::make_pair(GC_VirtualVolumeSize, ClientNetwork::GCVirtualVolumeSize));

	handle_map_.insert(std::make_pair(DC_ReadVolume, ClientNetwork::DCReadVolume));
	handle_map_.insert(std::make_pair(DC_VolumeSize, ClientNetwork::DCVolumeSize));
}
//创建卷
bool ClientNetwork::GCCreateVirtualVolume(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::GDCreateVolume nullptr == event || nullptr == data");
		return false;
	}
	GC_CreateVirtualVolumeMessage* pack = static_cast<GC_CreateVirtualVolumeMessage*>(data);
	if(promise_list_.empty())
	{
		LogError("ClientNetwork::GCCreateVirtualVolume promise_list_.empty()");
		return false;
	}
	std::cout << "ClientNetwork::GCCreateVirtualVolume code = " << pack->code_ << std::endl;
	std::promise<PromiseInfo>* promise = promise_list_.front();
	promise_list_.pop();
	if(nullptr == promise)
	{
		LogError("ClientNetwork::GCCreateVirtualVolume nullptr == promise");
		return false;
	}
	promise->set_value(&(pack->code_));
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
    promise->set_value(&(pack->code_));
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
    promise->set_value(&pack->code_);
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
		promise->set_value(&pack->code_);
		return false;
	}
	auto it = data_event_map_.find(pack->id_);
	if(data_event_map_.end() == it)
	{
		std::cerr << pack->ip_ << " " << pack->port_ << std::endl;
		ClientEvent* client_event = Connection(std::string(pack->ip_), pack->port_);
		if(nullptr == client_event)
		{
			LogError("ClientNetwork::GCReadVirtualVolume nullptr == client_event");
			return false;
		}
		data_event_map_.insert(std::make_pair(pack->id_, client_event));
	}
	it = data_event_map_.find(pack->id_);
	if(data_event_map_.end() == it)
	{
		LogError("ClientNetwork::GCReadVirtualVolume data_event_map_.end() == it");
		return false;
	}
	CD_ReadVolumeMessage msg;
	msg.header_.data_type_ = CD_ReadVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	memcpy(msg.name_, pack->name_, MaxVolumeNameSize);
	std::cerr << "**" << msg.name_ << "**" << std::endl;
	msg.orgin_ = pack->orgin_;
	msg.size_ = pack->size_;
	std::cerr << "++++++++++++++++++ " << std::endl;
	SendMessage(static_cast<void*>(it->second), static_cast<void*>(&msg), sizeof(msg));
	return true;
}

bool ClientNetwork::GCVirtualVolumeSize(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::CDVolumeSize nullptr == event || nullptr == data");
		return false;
	}
	GC_VirtualVolumeSizeMessage* pack = static_cast<GC_VirtualVolumeSizeMessage*>(data);
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
		promise->set_value(&pack->code_);
		return false;
		std::cerr << "fail" << std::endl;
	}
	auto it = data_event_map_.find(pack->id_);
	if(data_event_map_.end() == it)
	{
		std::cerr << pack->ip_ << " " << pack->port_ << std::endl;
		ClientEvent* client_event = Connection(std::string(pack->ip_), pack->port_);
		if(nullptr == client_event)
		{
			LogError("ClientNetwork::GCReadVirtualVolume nullptr == client_event");
			return false;
		}
		data_event_map_.insert(std::make_pair(pack->id_, client_event));
	}
	it = data_event_map_.find(pack->id_);
	if(data_event_map_.end() == it)
	{
		LogError("ClientNetwork::GCReadVirtualVolume data_event_map_.end() == it");
		return false;
	}
	CD_VolumeSizeMessage msg;
	msg.header_.data_type_ = CD_VolumeSize;
	msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	memcpy(msg.name_, pack->name_, MaxVolumeNameSize);
	std::cout << "__________" << std::endl;
	std::cerr << "**" << msg.name_ << "**" << std::endl;
	std::cerr << "++++++++++++++++++ " << std::endl;
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
	std::cerr << "----------" << pack->data_  << "-------------------"<< std::endl;
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
	if(Return_Fail == pack->code_)
	{
        LogError("ClientNetwork::DCReadVolume Return_Fail == pack->code_");
		promise->set_value(nullptr);
		return false;
	}
	promise->set_value(pack->data_);
	return true;
}

bool ClientNetwork::DCVolumeSize(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
	{
		LogError("ClientNetwork::DCReadVolume nullptr == event || nullptr == data");
		return false;
	}
	DC_VolumeSizeMessage* pack = static_cast<DC_VolumeSizeMessage*>(data);
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
	if(Return_Fail == pack->code_)
	{
        LogError("ClientNetwork::DCReadVolume Return_Fail == pack->code_");
		promise->set_value(nullptr);
		return false;
	}
	promise->set_value(&pack->size_);
	return true;
}


bool ClientNetwork::GCCreateUser(void* event, void* data)
{
	if(nullptr == event || nullptr == data)
    {   
        LogError("ClientNetwork::GCCreateUser nullptr == event || nullptr == data");
        return false;

    }   
    GC_CreateUserMessage* pack = static_cast<GC_CreateUserMessage*>(data);
    if(promise_list_.empty())
    {   
        LogError("ClientNetwork::GCCreateUser promise_list_.empty()");
        return false;
    }   
    std::promise<PromiseInfo>* promise = promise_list_.front();
    promise_list_.pop();
    if(nullptr == promise)
    {   
        LogError("ClientNetwork::GCCreateUser nullptr == promise");
        return false;
    }   
    promise->set_value(&(pack->code_));
    return true;	
}

ClientNetwork::ClientNetwork(const std::string& name, const std::string& pwd):
	MainEvent("127.0.0.1", 8888), CxxThread(), name_(name), pwd_(pwd) {}

ClientNetwork::~ClientNetwork() {}

bool ClientNetwork::CreateFile(const std::string& name)
{
	std::cerr << "name :" << name <<" " << MaxVolumeNameSize << std::endl;
	if(name.empty() || name.size() > MaxVolumeNameSize)
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
	std::future<PromiseInfo> future = promise.get_future();
	promise_list_.push(&promise);
	CG_CreateVirtualVolumeMessage msg;
	strcpy(msg.name_, name.c_str());
	msg.header_.data_type_ = CG_CreateVirtualVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
	std::cerr << "------------1" << std::endl;
	int	result = *static_cast<int*>(future.get().data_);
	std::cerr << "------------2" << result << std::endl;
	return Return_Fail != result;
}

bool ClientNetwork::DeleteFile(const std::string& name)
{
	if(name.empty() || name.size() > MaxVolumeNameSize)
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
    std::future<PromiseInfo> future = promise.get_future();
    promise_list_.push(&promise);
    CG_CreateVirtualVolumeMessage msg;
    strcpy(msg.name_, name.c_str());
    msg.header_.data_type_ = CG_DeleteVirtualVolume;
    msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
    SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
    int result = *static_cast<int*>(future.get().data_);
	std::cerr <<"ClientNetwork::DeleteFile result: " << result << std::endl;
	return Return_Fail != result;
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

	CG_UpdateVirtualVolumeMessage msg;
	msg.header_.data_type_ = CG_UpdateVirtualVolume;
	msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	memcpy(msg.name_, name.c_str(), name.size());
	std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> future = promise.get_future();
    promise_list_.push(&promise);

	int num = std::ceil(static_cast<double>(size) / MaxNetDataSize);
	size_t base_size = 0;
	for(int i = 1; i <= num; ++i)
	{
		size_t min_size = std::min(i * MaxNetDataSize, static_cast<int>(size - (i - 1) * MaxNetDataSize));
		msg.size_ = min_size;
		msg.orgin_ = base_size;
		memset(msg.data_, 0, sizeof(msg.data_));	
		memcpy(msg.data_, static_cast<void*>(static_cast<char*>(data) + base_size), min_size);
		SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
		base_size += (min_size + 1);
	}

	int result = *static_cast<int*>(future.get().data_);
	return Return_Fail != result;
}

bool ClientNetwork::ReadFile(const std::string& name, size_t orgin, void* data, size_t size)
{
	if(name.empty() || name.size() > MaxVolumeNameSize)
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
	strcpy(msg.name_, name.c_str());
	msg.orgin_ = orgin;
	msg.size_ = size;	
	msg.header_.data_type_ = CG_ReadVirtualVolume;
    msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	std::cerr << "###" << msg.name_ << "###" << std::endl;
	
	std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> future = promise.get_future();
    promise_list_.push(&promise);
    SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));	
	void* temp_data = future.get().data_;

	std::cout << "!!!!!!" << static_cast<char*>(temp_data) << std::endl;

	if(nullptr == temp_data)
	{
		return false;
	}
	memcpy(data, temp_data, size);
	if(nullptr == data)
	{	
		LogError("ClientNetwork::ReadFile nullptr == data");
		return false;
	}
	return true;
}

size_t ClientNetwork::SizeFile(const std::string& name)
{
	if(name.empty() || name.size() > MaxVolumeNameSize)
	{
		LogError("ClientNetwork::ReadFile name.empty() || name.size() > define MaxVolumeNameSize");
		return -1;
	}
	if(nullptr == gate_event_)
	{
		LogError("ClientNetwork::ReadFile nullptr == gate_event_");
		return -1;
	}
	
	CG_VirtualVolumeSizeMessage msg;
	strcpy(msg.name_, name.c_str());
	msg.header_.data_type_ = CG_VirtualVolumeSize;
    msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
	std::cerr << "###" << msg.name_ << "###" << std::endl;
	
	std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> future = promise.get_future();
    promise_list_.push(&promise);
    SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));	
	void* temp_data = future.get().data_;

	std::cout << "!!!!!!" << static_cast<char*>(temp_data) << std::endl;

	if(nullptr == temp_data)
	{
		return -1;
	}
	return *static_cast<int*>(temp_data);
	
}


bool ClientNetwork::CreateUser(const std::string& name, const std::string& password, const std::string& pwd)
{
	if(name.empty() || name.size() > MAX_USER_SIZE)
	{
		LogError("ClientNetwork::CreateUser name.empty() || name.size() > MAX_USER_SIZE");
		return false;
	}
	if(password.empty() || password.size() > MAX_PASSWORD_SIZE)
	{
		LogError("ClientNetwork::CreateUser password.empty() || password.size() > MAX_PASSWORD_SIZE");
		return false;
	}
	std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> future = promise.get_future();
    promise_list_.push(&promise);
    CG_CreateUserMessage msg;
    strcpy(msg.user_, name.c_str());
	strcpy(msg.password_, password.c_str());
	strcpy(msg.pwd_, pwd.c_str());
    msg.header_.data_type_ = CG_CreateUser;
    msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
    SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
    int result = *static_cast<int*>(future.get().data_);
    return Return_Fail != result;
}

bool ClientNetwork::CGConnection(const std::string& name, const std::string& pwd)
{
	if(name.empty() || name.size() > MAX_USER_SIZE)
    {   
        LogError("ClientNetwork::CreateUser name.empty() || name.size() > MAX_USER_SIZE");
        return false;
    }   
    if(pwd.empty() || pwd.size() > MAX_PASSWORD_SIZE)
    {   
        LogError("ClientNetwork::CreateUser password.empty() || password.size() > MAX_PASSWORD_SIZE");
        return false;
    }   
    std::promise<PromiseInfo> promise;
    std::future<PromiseInfo> future = promise.get_future();
    promise_list_.push(&promise);
    CG_ConnectionMessage msg;
    strcpy(msg.user_, name.c_str());
    strcpy(msg.pwd_, pwd.c_str());
    msg.header_.data_type_ = CG_Connection;
    msg.header_.data_size_ = sizeof(msg) - sizeof(NetDataHeader);
    SendMessage(static_cast<void*>(gate_event_), static_cast<void*>(&msg), sizeof(msg));
    int result = *static_cast<int*>(future.get().data_);
    return Return_Fail != result;
}

void ClientNetwork::ListenHandle(struct bufferevent* bev, struct sockaddr *sa, int socklen)
{
	ClientEvent* client_event = new ClientEvent(NetHandle);
	if(nullptr == client_event)
	{
		LogError("ClientNetwork::ListenHandle nullptr == data_event");
		return;
	}
	events_.push_back(client_event);
}

void ClientNetwork::Run(void)
{
//	Init();
//	gate_event_ = Connection(std::string("127.0.0.1"), 8888);
	RegisterProcess();
	Loop();
	std::cerr << "run" << std::endl;
}

void ClientNetwork::Instance()
{
	MainEvent::InstanceEventBase();
	_base = gEventBase;
//	Init();
  	gate_event_ = Connection(std::string("127.0.0.1"), 8888);
	Start();
}


















