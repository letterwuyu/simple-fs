#ifndef _DC_NET_STRUCT_H__
#define _DC_NET_STRUCT_H__
#include "dc_net_def.h"
DEFINE_MESSAGE_BEGIN(DC_ReadVolume)
	char name_[MaxVolumeNameSize];
	int32_t code_;
	size_t orgin_;
	size_t size_;
	char   data_[MaxNetDataSize];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(DC_VolumeSize)
    size_t size_;
    int32_t code_;
    void Clear()
    {   
        memset(this, 0, sizeof(*this));
    }   
DEFINE_MESSAGE_END

#endif //_DC_NET_STRUCT_H__
