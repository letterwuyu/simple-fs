#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H

#include "def.h"
#include "message_def.h"
#include "package_analysis.h"
#include <string.h>

DEFINE_MESSAGE_BEGIN(CS_CreateVolume)
struct VolumeInfo
{
	char name_[MAX_VOLUME_NAME];
	size_t content_;
};
VolumeInfo volume_info_;
void Clear()
{
	memset(this, 0, sizeof(*this));
}
DEFINE_MESSAGE_END 

DEFINE_MESSAGE_BEGIN(SC_CreateVolume)
sint32 return_code_;
void Clear()
{
	return_code_ = 10001;
}
DEFINE_MESSAGE_END 

DEFINE_MESSAGE_BEGIN(CS_DeleteVolume)
struct VolumeInfo
{
    char name_[MAX_VOLUME_NAME];
	sint32 client_id_;
};
VolumeInfo volume_info_;
void Clear()
{
	memset(this, 0, sizeof(*this));
}
DEFINE_MESSAGE_END 

DEFINE_MESSAGE_BEGIN(SC_DeleteVolume)
sint32 return_code_;
DEFINE_MESSAGE_END 

DEFINE_MESSAGE_BEGIN(GD_UpdateVolume)
struct Content
{
	uint64 volume_id_;
//	sint32_t client_id_;
	size_t orgin_;
	size_t size_;
	char   data_[0];
};
void Clear()
{
	memset(content_, 0, sizeof(*content_));
}
Content content_;
DEFINE_MESSAGE_END 

DEFINE_MESSAGE_BEGIN(SC_UpdateVolume)
sint32 return_code_;
void Clear()
{
	return_code_ = 10001;
}
DEFINE_MESSAGE_END 

DEFINE_MESSAGE_BEGIN(CS_LoadVolume)
struct VolumeInfo
{
    char name_[MAX_VOLUME_NAME];
    sint32 client_id_;
};
VolumeInfo volume_info_;
void Clear()
{
    memset(this, 0, sizeof(*this));
}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(SC_LoadVolume)
struct ChunkStream
{
	char   name_[MAX_VOLUME_NAME];
	size_t orgin_;
	size_t size_;
	char   data_[0];
}
ChunkStream chunk_stream_;
void Clear()
{
	memset(this, 0, sizeof(*this));
}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GD_CreateVolume)
void Clear()
{
//	memset(this, 0, sizeof(*this));
}
struct VolumeInfo
{
	uint64 volume_id_;
};
VolumeInfo volume_info_;
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(DG_HandShake)
void Clear()
{
	memset(server_info_, 0, sizeof(server_info_));
}
struct ServerInfo
{
	uint64 server_id;
};
ServerInfo server_info_;
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(CG_CreateVirtualVolume)
void Clear() {}
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_CreateVirtualVolume)
void Clear()
{
	memset(return_code_, 0, sizeof(return_code_));
}
struct ReturnCode
{
	sint32 code_;
};
ReturnCode return_code_;
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(CG_LoadVirtualVolume)
void Clear()
{
    memset(volume_info_, 0, sizeof(volume_info_));
}
struct VolumeInfo
{
	uint64 volume_id_;
}
VolumeInfo volume_info_;
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(GC_LoadVirtualVolume)
void Clear()
{
    memset(server_info_, 0, sizeof(server_info_));
}
struct ServerInfo
{
    uint64 server_id_;
}
ServerInfo server_info_;
DEFINE_MESSAGE_END

DEFINE_MESSAGE_BEGIN(CG_UpdateVirtualVolume)
struct Content
{
    uint64 volume_id_;
//    sint32_t client_id_;
    size_t orgin_;
    size_t size_;
    char   data_[0];
};
void Clear()
{
    memset(content_, 0, sizeof(*content_));
}
Content content_;
DEFINE_MESSAGE_END
#endif //MESSAGE_STRUCT_H













