#include "../../common/log4z/log4z.h"
#include "client_network.h"

using namespace zsummer::log4z;

int main(int argc, char**arhv)
{
	ILog4zManager::GetInstance()->Start();
	ClientNetwork client_network;
	client_network.Start();
	client_network.CreateFile("1");
	client_network.Join();
}
