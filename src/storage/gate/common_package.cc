#include "common_package.h"
#include "../../common/log4z/log4z.h"

CommonPackage::CommonPackage(void* pevent, void* pdata)
	:pevent_(pevent), pdata_(pdata) {}

CommonPackage::~CommonPackage() {}

void CommonPackage::SetEvent(void* pevent)
{
	if(nullptr == pevent)
	{
		LogError("CommonPackage::SetEvent nullptr == pevent");
		return;	
	}
	pevent_ = event;
}

void* CommonPackage::GetEvent(void)
{
	return pevent_;
}

void CommonPackage::SetData(void* pdata)
{
	if(nullptr == pdata)
	{
		LogError("CommonPackage::SetData nullptr == pdata)");
		return;
	}
	pdata_ = pdata;
}

void* CommonPackage::GetData(void)
{
	return pdata_;
}
