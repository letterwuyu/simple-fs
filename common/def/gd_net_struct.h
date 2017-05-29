#include "def.h"
#include "gd_net_def.h"

//创建卷
DEFINE_MESSAGE_BEGIN(GD_CreateVolume)
	char name_[MaxVolumeNameSize];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

//删除卷
DEFINE_MESSAGE_BEGIN(GD_DeleteVolume)
	char name_[MaxVolumeNameSize];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END

//写入卷
DEFINE_MESSAGE_BEGIN(GD_UpdateVolume)
	char name_[MaxVolumeNameSize];
	size_t orgin_;
	size_t size_;
	char   buffer_[MaxNetDataSize];
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
DEFINE_MESSAGE_END
