#include "gate_server.h"
#include "data_server_manager.h"
#include "virtual_volume_manager.h"

GateSocket::GateSocket():package_analysis_(GateSocket::HandleNetPack){}

HandleMap GateSocket::handle_map_;

bool GateSocket::InitHandleMap()
{
	handle_map_.insert(make_pair(DG_HandShake, function<bool(void*, void*)>(ClassHandle(DG_HandShake) )));
	handle_map_.insert(make_pair(CG_CreateVirtualVolume, function<bool(void*, void*)>(ClassHandle(CG_CreateVirtualVolume) )));
	handle_map_.insert(make_pair(CG_LoadVirtualVolume, function<bool(void*, void*)>(ClassHandle(CG_LoadVirtualVolume) )));
    handle_map_.insert(make_pair(CG_UpdateVirtualVolume, function<bool(void*, void*)>(ClassHandle(CG_UpdateVirtualVolume) )));
	return true;
}

void GateSocket::HandleNetPack(void* header)
{
	if(NULL == header)
		return;
	handle_map_[static_cast<NetDataHeader*>(header)->header_->data_type_](this, header);
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













