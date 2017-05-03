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

DEFINE_MESSAGE_BEGIN(CS_UpdateVolume)
struct Content
{
	char name_[MAX_VOLUME_NAME];
	sint32_t client_id_;
	size_t orgin_;
	size_t size_;
	char   data_[0];
};
void Clear()
{
	memset(this, 0, sizeof(*this));
}
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

#endif //MESSAGE_STRUCT_H
