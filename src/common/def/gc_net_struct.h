#ifndef _GC_NET_STRUCT_H__
#define _GC_NET_STRUCT_H__

#include "gc_net_def.h"

DEFINE_MESSAGE_BEGIN(GC_CreateVirtualVolume)
	int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_DeleteVirtualVolume)
	int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_UpdateVirtualVolume)
	int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_ReadVirtualVolume)
	int32_t id_;
	char ip_[MaxIpSize];
	int32_t port_;
    char name_[MaxVolumeNameSize];
	size_t orgin_;
	size_t size_;
	int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_CreateUser)
    int32_t code_;
    void Clear()
    {   
        memset(this, 0, sizeof(*this));
    }   
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_Connection)
    int32_t code_;
    void Clear()
    {   
        memset(this, 0, sizeof(*this));
    }   
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_VirtualVolumeSize)
    int32_t id_;
    char ip_[MaxIpSize];
    int32_t port_;
    char name_[MaxVolumeNameSize];
    int32_t code_;
    void Clear()
    {   
        memset(this, 0, sizeof(*this));
    }   
DEFINE_MESSAGE_END


#endif //_GC_NET_STRUCT_H__
