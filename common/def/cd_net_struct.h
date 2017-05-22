#ifndef _CD_NET_STRUCT_H__
#define _CD_NET_STRUCT_H__
#include "cd_net_def.h"
//读取卷
DEFINE_MESSAGE_BEGIN(CD_ReadVolume)
	char   name_[MaxVolumeNameSize];
	size_t orgin_;
	size_t size_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END
#endif //_CD_NET_STRUCT_H__
