#ifndef _CG_NET_STRUCT_H__
#define _CG_NET_STRUCT_H__
#include "cg_net_def.h"

DEFINE_MESSAGE_BEGIN(CG_CreateVirtualVolume)
	char name_[MaxVolumeNameSize];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(CG_DeleteVirtualVolume)
	char name_[MaxVolumeNameSize];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(CG_UpdateVirtualVolume)
	char name_[MaxVolumeNameSize];
	size_t orgin_;
	size_t size_;
	char   data_[0];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(CG_ReadVirtualVolume)
	char name_[MaxVolumeNameSize];
	size_t orgin_;
	size_t size_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

#endif //_CG_NET_STRUCT_H__
