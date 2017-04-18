#ifndef _PACKAGE_ANALYSIS_H__
#define _PACKAGE_ANALYSIS_H__
#include <string.h>
#include <unordered_map>
namespace net {

const size_t kMaxNetPackSize = 10000;
const size_t kMaxDataSize = 4086;

struct NetDataHeader_t
{
	int32_t nDataType;
	int32_t nDataSize;
};

struct NetDataBase_t
{
	NetDataHeader_t dataHeader;
	char szData[kMaxDataSize];
};

struct NetReceiveData_t
{
	NetReceiveData_t()
	{
		nRemainSize = 0;
		bFirst = true;
	}	
	char szLastSaveData[kMaxNetPackSize];
	size_t nRemainSize;
	bool bFirst;
};

class PackageAnalysis {
public:
	PackageAnalysis();
	virtual ~PackageAnalysis();
	PackageAnalysis(const PackageAnalysis&) = delete;
public:
	void Register(int32_t id);
	bool TcpDataSplit(int32_t id, const char* recv_data, size_t recv_size);
	virtual HandleNetPack(NetDataHeader_t* data_header) = 0;
private:
	std::unordered_map<sint32_t, NetReceiveData_t> receive_packages_;
};

}

#endif //_PACKAGE_ANALYSIS_H__

