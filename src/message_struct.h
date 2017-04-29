#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H

#include "def.h"
#include "message_def.h"
#include "package_analysis.h"
#include <string.h>

DEFINE_MESSAGE_BEGIN(SC_StroageData)
	struct StorageData
	{
		char data_[1024];
		int  volume_id_;
	};
	StorageData storage_data_;
	void Clear()
	{
		memset(this, 0, sizeof(*this));	
	}
DEFINE_MESSAGE_END
#endif //MESSAGE_STRUCT_H
