#ifndef _PACKAGE_ANALYSIS_H__
#define _PACKAGE_ANALYSIS_H__
#include <string.h>
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
	PackageAnalysis(HandleNetPackType& handle);
	virtual ~PackageAnalysis();
    PackageAnalysis() = delete;
	PackageAnalysis(const PackageAnalysis&) = delete;
public:
	typedef std::functional<void (NetDataHeader*)> HandleNetPackType;
	bool TcpDataSplit(int32_t id, const char* recv_data, size_t recv_size);
private:
	char last_save_data_[kMaxNetPackSize];
    size_t remain_size_;
    bool first_;
	HandleNetPackType handle_net_pack_;
};

#define CONSTRUCT_NET_PACKAGE(name, type) char name[sizeof(type)]; \
	memcpy(name, reinterpret_cast<char*>(&type), sizeof(type));

}

template<typename DataType>
struct Package
{
	NetDataBase data_header_;
	DataType data_;
};

#endif //_PACKAGE_ANALYSIS_H__

