#ifndef CLINET_CROCESS_H
#define CLINET_PROCESS_H
#include "def.h"
#include "inc.h"
#include "enum.h"
#include "client_service.h"

bool ServiceEvent::Client_Handle(SC_CreateVolume)
{
	UN_CLIENT_PACKAGE(SC_CreateVolume);
}

bool ServiceEvent::Client_Handle(CS_CreateVolume)
{
	 UN_CLIENT_PACKAGE(CS_CreateVolume);
	 pServer->Write(pdata->buffer_, pdata->size_);
}

bool ServiceEvent::Client_Handle(CS_DeleteVolume)
{
	UN_CLIENT_PACKAGE(CS_DeleteVolume);
    pServer->Write(pdata->buffer_, pdata->size_);
}

bool ServiceEvent::Client_Handle(SC_DeleteVolume)
{
	UN_CLIENT_PACKAGE(SC_DeleteVolume);
}

bool ServiceEvent::Client_Handle(CS_UpdateVolume)
{
	UN_CLIENT_PACKAGE(CS_UpdateVolume);
	pServer->Write((pdata->buffer_, pdata->size_);	
}

bool ServiceEvent::Client_Handle(SC_UpdateVolume)
{
	UN_CLIENT_PACKAGE(SC_UpdateVolume);
}

bool ServiceEvent::Client_Handle(CS_LoadVolume)
{
	UN_CLIENT_PACKAGE(CS_LoadVolume);
    pServer->Write((pdata->buffer_, pdata->size_); 
}

bool ServiceEvent::Client_Handle(SC_LoadVolume)
{
	UN_CLIENT_PACKAGE(SC_LoadVolume);
    int fd = open(pPack->chunk_stream_->name_, O_RDWR);
	lseek(fd, chunk_stream->orgin_, SEEK_SET);
	write(fd, chunk_stream_->data_, chunk_stream_->size_);
}
#endif //CLINET_PROCESS_H








