#include "dg_net+def.h"
#include "def.h"

// 创建卷
DEFINE_MESSAGE_BEGIN(DG_CreateVolume)
	int32_t code_;
DEFINE_MESSAGE_END

//删除卷
DEFINE_MESSAGE_BEGIN(DG_DeleteVolume)
    int32_t code_;
DEFINE_MESSAGE_END

//写入卷
DEFINE_MESSAGE_BEGIN(DG_UpdateVolume)
    int32_t code_;
DEFINE_MESSAGE_END
