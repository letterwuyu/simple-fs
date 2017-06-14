#ifndef _TEST_MESSAGE_H__
#define _TEST_MESSAGE_H__
#include "package_analysis.h"
#include <string.h>
using namespace net;
struct Message
{
	Message()
	{
		memset(this, 0 , sizeof(*this));
	}
	NetDataHeader header_;
	size_t s;
	char a[0];
};

#endif //_TEST_MESSAGE_H__
