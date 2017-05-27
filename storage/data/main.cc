#include "../../common/log4z/log4z.h"
#include "data_server.h"

using namespace zsummer::log4z;

int main(int argc, char** argv)
{
	//stat log
	ILog4zManager::GetInstance()->Start();
	
	DataServer data_server;
	data_server.Start();
	data_server.Join();
}
