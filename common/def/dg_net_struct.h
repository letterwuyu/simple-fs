#ifndef _DG_NET_STRUCT_H__
#define _DG_NET_DTRUCT_H__

#include "dg_net_def.h"
#include "def.h"

// 创建卷
DEFINE_MESSAGE_BEGIN(DG_CreateVolume)
	int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

//删除卷
DEFINE_MESSAGE_BEGIN(DG_DeleteVolume)
    int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

//写入卷
DEFINE_MESSAGE_BEGIN(DG_UpdateVolume)
    int32_t code_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(DG_Shake)
    int32_t id_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

#endif //_DG_NET_STRUCT_H__
