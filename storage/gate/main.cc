#include "../../common/def/def.h"
#include "../../common/log4z/log4z.h"
#include "gate_server.h"

using namespace zsummer::log4z;

int main(int argc, char **argv)
{
	//启动日志
	ILog4zManager::GetInstance()->Start(); 
	//构建网关服务
	GateServer gate_server;
	//初始化网关服务
//	gate_server.Init();
	//启动网关服务
	gate_server.Start();
	gate_server.Join();
}
