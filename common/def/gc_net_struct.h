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
	int32_t code_;
    char name_[define MaxVolumeNameSize];
	size_t orgin_;
	size_t size_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

#endif //_GC_NET_STRUCT_H__
