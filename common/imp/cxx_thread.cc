#include "cxx_thread.h"

void CxxThread::Start(void)
{
	future = std::async(std::launch::async, std::bind(&CxxThread::Run, this));
}

void CxxThread::Join()
{
	future.get();
}
