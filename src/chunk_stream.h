#ifndef _CHUNK_STREAM_H_
#define _CHUNK_STREAM_H_
#include "package_analysis.h"

struct NetChunkStream
{
	NetDataHeader header_;
	size_t chunk_size_;
	void   chunk_data_[0];
};

#endif //_CHUNK_STREAM_H_
