#include <iostream>
#include <glog/logging.h>

int main(int argc, char **argv)
{
	//FLAGS_log_dir = ".";
	google::InitGoogleLogging(argv[0]);
	LOG(INFO) << "info hello world";
	LOG(WARNING) << "warning hello world";
	LOG(ERROR) << "error hello world";
	return 0;
}
