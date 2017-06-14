#include "../../common/log4z/log4z.h"
#include "client_network.h"
#include <chrono>
#include <thread>

using namespace zsummer::log4z;

int main(int argc, char**argv)
{
	ILog4zManager::GetInstance()->Start();
	ClientNetwork client_network("111", "222");
	client_network.Instance();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	client_network.CreateFile("1");
	char buffer[] = "hello world";
	client_network.WriteFile("1", 0, buffer, 12);
	size_t size = client_network.SizeFile("1");
	char buf[12];
	client_network.ReadFile("1", 0, buf, 12);
	char bufferr[] = "zi ji ba zi ji keng le";
	client_network.WriteFile("1", 0, bufferr, strlen(bufferr));
	client_network.ReadFile("1", 0, buf, 12);
//	client_network.DeleteFile("1");
	client_network.Join();
}
