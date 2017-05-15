#include "package_analysis.h"
#include <assert.h>
namespace net {
PackageAnalysis::PackageAnalysis(/*PackageAnalysis::HandleType handle*/)
	:/*handle_net_pack_(handle), */remain_size_(0), first_(true)
{
	memset(last_save_data_, 0 , sizeof(last_save_data_));
}

bool PackageAnalysis::TcpDataSplit(const char* recv_data, size_t recv_size)
{
	if(first_)
	{
		memset(last_save_data_, 0, sizeof(last_save_data_));
		first_ = 0;
	}
	memcpy(static_cast<char*>(last_save_data_ + remain_size_), recv_data, recv_size);
	remain_size_ += recv_size;
	NetDataHeader* data_head = reinterpret_cast<NetDataHeader*>(last_save_data_);
	while(remain_size_ > sizeof(NetDataHeader) && remain_size_ >= sizeof(NetDataHeader) + data_head->data_size_)
	{
		//handle_net_pack_(data_head);
		HandleNetPack(data_head);
		size_t rec_object_size = sizeof(NetDataHeader) + data_head->data_size_;
		remain_size_ -= rec_object_size;
	}
	if(last_save_data_ != reinterpret_cast<char*>(data_head))
	{
		memmove(last_save_data_, reinterpret_cast<char*>(data_head), remain_size_);
		memset(last_save_data_ + remain_size_, 0, sizeof(last_save_data_) - remain_size_);
	}
	return true;
}

void PackageAnalysis::HandleNetPack()
{
	//此处设置断言，防止继承类没有重写HandleNetPack
	assert(false);
}
