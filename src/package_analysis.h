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
	typedef std::function<bool(void*, void*)> HandleMap;
	PackageAnalysis();
	bool TcpDataSplit(const char* recv_data, size_t recv_size);
	bool HandleNetPack(void* control, void* package);
protected:
	char last_save_data_[kMaxNetPackSize];
    size_t remain_size_;
    bool first_;
	HandleMap handle_map_;
};

template<typename DataType>
struct Package
{
	NetDataHeader data_header_;
	DataType data_;};

}
#endif //_PACKAGE_ANALYSIS_H__

