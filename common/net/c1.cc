#include "package_analysis.h"
#include <iostream>
struct People
{
	char name_[100];
	int32_t age_;
};

void handle(void *p)
{
	net::NetDataHeader* pdata = static_cast<net::NetDataHeader*>(p);
	if(pdata-> data_type_ = 1)
	{
		net::Package<People>* p = reinterpret_cast<net::Package<People>*>(pdata);
		std::cout << p->data_.name_ << std::endl;
		std::cout << p->data_.age_ << std::endl;
	}

}

int main()
{
	typedef net::Package<People> people_type;
	people_type p;
	p.data_header_.data_size_ = sizeof(people_type) - sizeof(net::NetDataHeader);
	p.data_header_.data_type_ = 1;
	p.data_.age_ = 10;
	sprintf(p.data_.name_, "hello");
	char s[sizeof(people_type)];
//	memcpy(s, reinterpret_cast<char*>(&p), sizeof(p));
	net::PackageAnalysis PP(handle);
	PP.TcpDataSplit(reinterpret_cast<char*>(&p), sizeof(p));
	PP.TcpDataSplit(reinterpret_cast<char*>(&p), sizeof(p));
}
