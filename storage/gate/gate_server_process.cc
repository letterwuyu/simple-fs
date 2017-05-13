#include "gate_server.h"

ClassHandle(GateSocket, DG_HandShake)
{
	GATE_UNPACK(DG_HandShake, data);
	singleton<DataServerManager>::intance().Addserver(this, pack->server_info_.server_id_);
	return true;
}

ClassHandle(GateSocket, CG_CreateVirtualVolume)
{
	uint64 id = singleton<VirtualVolumeManager>::intance().CreateVirtualVolume();
    CONSTRUCT_MESSAGE(GC_CreateVirtualVolume);
    
    if(id > 0)
    	msg->return_code_.code_ = 1;
    else
       	msg->return_code_.code_ = 0;

	SocketEvent* gate_event = static_cast<SocketEvent*>(event);
    gate_event->write(reinterpret_cast<char*>(&msg), sizeof(msg));
	return true;
}

ClassHandle(GateSocket, CG_LoadVirtualVolume)
{
	GATE_UNPACK(CG_LoadVirtualVolume, data);
	shared_ptr<VirtualVolume> sp = GSingle(VirtualVolumeManager).GetVirtualVolume(pack.volume_info_.volume_id_);
    vector<uint64> servers = sp->GetServers();
    CONSTRUCT_MESSAGE(GC_LoadVirtualVolume);
    if(servers.empty())
    	msg.server_info_.server_id_ = 0;
    else
        msg.server_info_.server_id_ = servers[0];

	SocketEvent* gate_event = static_cast<SocketEvent*>(event);
    write(reinterpret_cast<char*>(&msg), sizeof(msg));
	return true;
}

ClassHandle(GateSocket, CG_UpdateVirtualVolume)
{
	GATE_UNPACK(CG_UpdateVirtualVolume, data);
	CONSTRUCT_MESSAGE(GD_UpdateVolume);
            
	memcpy(msg.content_, pack.content_, sizeof(pack.content_));
    shared_ptr<VirtualVolume> sp = CSingle(VirtualVolumeManager).GetVirtualVolume(pack.volume_info_.volume_id_);
    vector<uint64> servers = sp->GetServers();
    for(auto it = servers.begin(); it != servers.end(); ++it)
    {
       auto sp = CSingle(DataServerManager>).GetServer(*it);
       sp->write(reinterpret_cast<char*>(msg), sizeof(msg));
	}
}












