#ifndef _PACKAGE_ANALYSIS_H__
#define _PACKAGE_ANALYSIS_H__
#include <string.h>
#include <stdint.h>
#include <functional>
#include <unordered_map>
namespace net {

const size_t kMaxNetPackSize = 10000;
const size_t kMaxDataSize = 4086;

struct NetDataHeader
{
	int32_t data_type_;
	int32_t data_size_;
};

struct NetDataBase
{
	NetDataHeader data_header_;
	char data_[kMaxDataSize];
};

class PackageAnalysis {
public:
    typedef void (*HandleType)(void*);
    PackageAnalysis(HandleType handle);
	bool TcpDataSplit(const char* recv_data, size_t recv_size);
private:
	char last_save_data_[kMaxNetPackSize];
	HandleType handle_net_pack_;
    size_t remain_size_;
    bool first_;
//	void HandleNetPack(void* header);
};

template<typename DataType>
struct Package
{
	NetDataHeader data_header_;
	DataType data_;
};

}
#endif //_PACKAGE_ANALYSIS_H__

