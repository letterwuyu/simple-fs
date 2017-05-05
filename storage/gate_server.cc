#include "gate_server.h"
#include "data_server_manager.h"
#include "virtual_volume_manager.h"

GateSocket::GateSocket()remain_size_(0), first_(true)
{
	memset(last_save_data_, 0 , sizeof(last_save_data_));
}

void GateSocket::ReadHandle(struct bufferevent* bev)
{
	struct evbuffer *input = bufferevent_get_input(bev);
    size_t sz = evbuffer_get_length(input);
    char* buffer = new char[sz]();
    memset(buffer, 0, sz);
    if(sz > 0)
    {   
        bufferevent_read(bev, buffer, sz);
        TcpDataSplit(buffer, sz);
    }   
}

bool GateSocket::TcpDataSplit(const char* recv_data, size_t recv_size)
{
	if(first_)
    {   
        memset(last_save_data_, 0, sizeof(last_save_data_));
        first_ = 0;
    }   
    memcpy(static_cast<char*>(last_save_data_ + remain_size_), recv_data, recv_size);
    remain_size_ += recv_size;
    NetDataHeader* data_head = reinterpret_cast<NetDataHeader*>(last_save_data_);
    while(remain_size_ > sizeof(NetDataHeader) && remain_size_ >= sizeof(NetDataHeader) + data_head->data_size_)
    {   
        HandleNetPack(data_head);
        size_t rec_object_size = sizeof(NetDataHeader) + data_head->data_size_;
        remain_size_ -= rec_object_size;
    }   
    if(last_save_data_ != reinterpret_cast<char*>(data_head))
    {   
        memmove(last_save_data_, reinterpret_cast<char*>(data_head), remain_size_);
        memset(last_save_data_ + remain_size_, 0, sizeof(last_save_data_) - remain_size_);
    }   
    return true;
}

void GateSocket::HabdleNetPack(NetDataHeader* header)
{
	switch(header->data_type_)
	{
		case DG_HandShake:
		{
			GATE_UNPACK(DG_HandShake, header);
			singleton<DataServerManager>::intance().Addserver(this, pack->server_info_.server_id_);
		};
		break;
		
		case CG_CreateVirtualVolume:
		{
			uint64 id = singleton<VirtualVolumeManager>::intance().CreateVirtualVolume();
			CONSTRUCT_MESSAGE(GC_CreateVirtualVolume);
	
			if(id > 0)
				msg->return_code_.code_ = 1;
			else
				msg->return_code_.code_ = 0;
			write(reinterpret_cast<char*>(&msg), sizeof(msg));
		};
		break;
		
		case CG_LoadVirtualVolume
		{
			GATE_UNPACK(CG_LoadVirtualVolume, header);
			shared_ptr<VirtualVolume> sp =singleton<VirtualVolumeManager>::intance().GetVirtualVolume(pack.volume_info_.volume_id_);
			vector<uint64> servers = sp->GetServers();
			CONSTRUCT_MESSAGE(GC_LoadVirtualVolume);
			if(servers.empty())
				msg.server_info_.server_id_ = 0;
			else
				msg.server_info_.server_id_ = servers[0];
			write(reinterpret_cast<char*>(&msg), sizeof(msg));
		};
		break;

		case CG_UpdateVirtualVolume
		{
			GATE_UNPACK(CG_UpdateVirtualVolume, header);
			CONSTRUCT_MESSAGE(GD_UpdateVolume);
			memcpy(msg.content_, pack.content_, sizeof(pack.content_));
			hared_ptr<VirtualVolume> sp =singleton<VirtualVolumeManager>::intance().GetVirtualVolume(pack.volume_info_.volume_id_);
            vector<uint64> servers = sp->GetServers();
			for(auto it = servers.begin(); it != servers.end(); ++it)
			{
				auto sp = singleton<DataServerManager>::intance().GetServer(*it);
				sp->write(reinterpret_cast<char*>(msg), sizeof(msg));
			}
		};
		break;
		default ; break;
	}	
}

void GateServer::ListenHandle(struct bufferevent *bev)
{
	shared_ptr<GateSocket> sp = make_shared<GateSocket>();
	sp->SetBuffer(bev);
	sp->Init();
	sockets_.push_back(bev);
}

void GateServer::Run()
{
	 Init();
 	 Loop();

}













