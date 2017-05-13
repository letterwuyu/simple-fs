#include "package_analysis.h"

void func(net::NetDataHeader*) {}
int main()
{
	net::PackageAnalysis P;
	P.TcpDataSplit(NULL, 0);
}
